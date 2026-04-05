#include "pch.h"
#include "SpineTriggersSystem.h"
#include "EventBattleSystem.h"

HopEngine::SpineTriggerSystem* HopEngine::SpineTriggerSystem::Instance()
{
    static SpineTriggerSystem SpineTriggerSystem;
    return &SpineTriggerSystem;
}

void HopEngine::SpineTriggerSystem::Update()
{
    for (size_t i = 0; i < hitboxes.size(); ++i)
    {
        auto& rec_i = hitboxes[i];
        auto verts_i = getHitboxWorldVertices(rec_i.spine->getSkeletonTransform(),
            rec_i.boneName, rec_i.hitboxName);

        for (size_t j = i + 1; j < hitboxes.size(); ++j)
        {
            auto& rec_j = hitboxes[j];
            if (rec_i.spine == rec_j.spine) continue;

            auto verts_j = getHitboxWorldVertices(rec_j.spine->getSkeletonTransform(),
                rec_j.boneName, rec_j.hitboxName);

            bool intersect = checkHitboxIntersectionSAT(verts_i, verts_j);

            auto it = triggersEnteredPair.find(rec_i.owner);
            bool alreadyActive = (it != triggersEnteredPair.end() && it->second == rec_j.owner);

            if (intersect && !alreadyActive)
            {
                EventBattleSystem::Instance()->TriggerEvent(rec_i.owner, rec_i.hitboxName,
                    rec_j.owner, rec_j.hitboxName);
                triggersEnteredPair.emplace(rec_i.owner, rec_j.owner);
            }
            else if (!intersect && alreadyActive)
            {
                triggersEnteredPair.erase(it);
            }
        }
    }
}

void HopEngine::SpineTriggerSystem::Subscribe_HitBoxes(GameObject* owner, SpineComponent* data,
    spine::String bone_name, spine::String hitbox_name)
{
    hitboxes.push_back({ owner, data, bone_name, hitbox_name });
}

void HopEngine::SpineTriggerSystem::Unsubscribe_HitBoxes(GameObject* owner, SpineComponent* data,
    spine::String bone_name, spine::String hitbox_name)
{
    auto it = std::remove_if(hitboxes.begin(), hitboxes.end(),
        [=](const HitboxRecord& rec) {
            return rec.owner == owner && rec.spine == data &&
                rec.boneName == bone_name && rec.hitboxName == hitbox_name;
        });
    hitboxes.erase(it, hitboxes.end());
}

std::vector<sf::Vector2f> HopEngine::SpineTriggerSystem::getHitboxWorldVertices(spine::Skeleton* skeleton, spine::String slotName, spine::String attachmentName)
{
    std::vector<sf::Vector2f> result;

    if (!skeleton) return result;

    skeleton->updateWorldTransform();

    spine::Slot* slot = skeleton->findSlot(slotName);
    if (!slot) return result;

    spine::Skin* skin = skeleton->getSkin();
    if (!skin) return result;

    spine::Attachment* attachment = skeleton->getAttachment(slot->getData().getIndex(), attachmentName);
    if (!attachment) return result;

    spine::BoundingBoxAttachment* bbox = dynamic_cast<spine::BoundingBoxAttachment*>(attachment);
    if (!bbox) return result;

    const spine::Vector<float>& localVerts = bbox->getVertices();
    int vertexCount = localVerts.size() / 2;
    if (vertexCount == 0) return result;

    std::vector<float> worldVerts(vertexCount * 2);

    bbox->computeWorldVertices(
        *slot,
        0,
        vertexCount * 2,
        worldVerts.data(),
        0,
        2
    );

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
