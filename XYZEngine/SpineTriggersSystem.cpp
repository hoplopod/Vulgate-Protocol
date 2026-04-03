#include "pch.h"
#include "SpineTriggersSystem.h"

void HopEngine::SpineTriggerSystem::Update() {

	for (int i = 0; i < hitboxes.size(); ++i) {

        auto hitbox_1 = getHitboxWorldVertices(hitboxes[i].first->getSkeletonTransform(), hitboxes[i].second.first, hitboxes[i].second.second);

        for (int j = 0; j < hitboxes.size(); ++j) {
            
            if (i == j) continue;
            if (hitboxes[i].first == hitboxes[j].first) continue;

            auto hitbox_2 = getHitboxWorldVertices(hitboxes[j].first->getSkeletonTransform(), hitboxes[j].second.first, hitboxes[j].second.second);

            if (checkHitboxIntersectionSAT(hitbox_1, hitbox_2)) {
                if (triggersEnteredPair.find(collider[i]) == triggersEnteredPair.end() && triggersEnteredPair.find(collider[j]) == triggersEnteredPair.end())
                {
                    auto trigger = new Trigger(collider[i], collider[j]);
                    collider[i]->OnTriggerEnter(*trigger);
                    collider[j]->OnTriggerEnter(*trigger);

                    triggersEnteredPair.emplace(collider[i], collider[j]);
                }
            }
            else if (triggersEnteredPair.find(collider[i]) != triggersEnteredPair.end() && triggersEnteredPair.find(collider[j]) != triggersEnteredPair.end()) {
                auto trigger = new Trigger(collider[i], collider[j]);
                collider[i]->OnTriggerExit(*trigger);
                collider[j]->OnTriggerExit(*trigger);

                triggersEnteredPair.erase(triggersEnteredPair.find(collider[i]));
            }
        }
        
	}
}

void HopEngine::SpineTriggerSystem::Subscribe_HitBoxes(ColliderComponent* new_collider, SpineComponent* data, spine::String bone_name, spine::String hitbox_name)
{
	std::cout << "Subscribe " << data << std::endl;
	hitboxes.push_back(std::make_pair(data, std::make_pair(bone_name, hitbox_name)));
    collider.push_back(new_collider);
}

void HopEngine::SpineTriggerSystem::Unsubscribe_HitBoxes(ColliderComponent* new_collider, SpineComponent* data, spine::String bone_name, spine::String hitbox_name)
{
    std::cout << "Unsubscribe " << data << std::endl;

    auto target = std::make_pair(data, std::make_pair(bone_name, hitbox_name));

    hitboxes.erase(std::remove_if(hitboxes.begin(), hitboxes.end(), [&target](const auto& obj) { return obj == target; }), hitboxes.end());
    collider.erase(std::remove_if(collider.begin(), collider.end(), [new_collider](ColliderComponent* obj) {return obj == new_collider; }), collider.end());

}

std::vector<sf::Vector2f> HopEngine::SpineTriggerSystem::getHitboxWorldVertices(spine::Skeleton* skeleton, spine::String boneName, spine::String attachmentName)
{
    std::vector<sf::Vector2f> result;

    spine::Slot* slot = skeleton->findSlot(boneName);
    if (!slot) return result;

    spine::Attachment* attachment = skeleton->getAttachment(slot->getData().getIndex(), attachmentName);
    if (!attachment) return result;

    spine::BoundingBoxAttachment* bbox = dynamic_cast<spine::BoundingBoxAttachment*>(attachment);
    if (!bbox) return result;

    const spine::Vector<float>& localVerts = bbox->getVertices();
    int vertexCount = localVerts.size() / 2;
    if (vertexCount == 0) return result;

    std::vector<float> worldVerts(vertexCount * 2);

    bbox->computeWorldVertices(*slot, 0, vertexCount * 2, worldVerts.data(), 0, sizeof(float));

    result.reserve(vertexCount);
    for (int i = 0; i < vertexCount; ++i) {
        result.emplace_back(worldVerts[i * 2], worldVerts[i * 2 + 1]);
    }

    return result;
}

HopEngine::Projection HopEngine::SpineTriggerSystem::projectPolygon(const std::vector<sf::Vector2f>& poly, const sf::Vector2f& axis) {
    float dot = axis.x * poly[0].x + axis.y * poly[0].y;
    float min = dot, max = dot;
    for (size_t i = 1; i < poly.size(); ++i) {
        dot = axis.x * poly[i].x + axis.y * poly[i].y;
        if (dot < min) min = dot;
        if (dot > max) max = dot;
    }
    return { min, max };
}

bool HopEngine::SpineTriggerSystem::overlap(const Projection& p1, const Projection& p2) {
    return !(p1.max < p2.min || p2.max < p1.min);
}

sf::Vector2f HopEngine::SpineTriggerSystem::getNormal(const sf::Vector2f& p1, const sf::Vector2f& p2) {
    sf::Vector2f edge = p2 - p1;
    return sf::Vector2f(-edge.y, edge.x);
}

bool HopEngine::SpineTriggerSystem::checkHitboxIntersectionSAT(const std::vector<sf::Vector2f>& a,
    const std::vector<sf::Vector2f>& b) {
    if (a.size() < 3 || b.size() < 3) return false;

    for (size_t i = 0; i < a.size(); ++i) {
        const sf::Vector2f& p1 = a[i];
        const sf::Vector2f& p2 = a[(i + 1) % a.size()];
        sf::Vector2f axis = getNormal(p1, p2);
        float len = std::sqrt(axis.x * axis.x + axis.y * axis.y);
        if (len < 1e-6f) continue;
        axis /= len;

        Projection projA = projectPolygon(a, axis);
        Projection projB = projectPolygon(b, axis);
        if (!overlap(projA, projB)) return false;
    }

    for (size_t i = 0; i < b.size(); ++i) {
        const sf::Vector2f& p1 = b[i];
        const sf::Vector2f& p2 = b[(i + 1) % b.size()];
        sf::Vector2f axis = getNormal(p1, p2);
        float len = std::sqrt(axis.x * axis.x + axis.y * axis.y);
        if (len < 1e-6f) continue;
        axis /= len;

        Projection projA = projectPolygon(a, axis);
        Projection projB = projectPolygon(b, axis);
        if (!overlap(projA, projB)) return false;
    }

    return true;
}
