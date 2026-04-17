#include "pch.h"
#include "SpineTriggersSystem.h"
#include "EventBattleSystem.h"

HopEngine::SpineTriggerSystem* HopEngine::SpineTriggerSystem::Instance()
{
    static SpineTriggerSystem instance;
    return &instance;
}

void HopEngine::SpineTriggerSystem::Update()
{
    currentFramePairs.clear(); 

    auto makePair = [](GameObject* a, GameObject* b,
        const std::string& boneA,
        const std::string& hitboxA,
        const std::string& boneB,
        const std::string& hitboxB)
        {
            if (a < b)
                return HitPair{ a, b, boneA, hitboxA, boneB, hitboxB };
            else
                return HitPair{ b, a, boneB, hitboxB, boneA, hitboxA };
        };

    for (size_t i = 0; i < hitboxes.size(); ++i)
    {
        auto& rec_i = hitboxes[i];

        auto verts_i = getHitboxWorldVertices(
            rec_i.spine->getSkeletonTransform(),
            rec_i.boneName,
            rec_i.hitboxName);

        for (size_t j = i + 1; j < hitboxes.size(); ++j)
        {
            auto& rec_j = hitboxes[j];

            if (rec_i.spine == rec_j.spine)
                continue;

            auto verts_j = getHitboxWorldVertices(
                rec_j.spine->getSkeletonTransform(),
                rec_j.boneName,
                rec_j.hitboxName);

            bool intersect = checkHitboxIntersectionSAT(verts_i, verts_j);

            std::string boneA = rec_i.boneName.buffer();
            std::string hitboxA = rec_i.hitboxName.buffer();

            std::string boneB = rec_j.boneName.buffer();
            std::string hitboxB = rec_j.hitboxName.buffer();

            auto pair = makePair(
                rec_i.owner, rec_j.owner,
                boneA, hitboxA,
                boneB, hitboxB);

            bool alreadyActive = activePairs.count(pair) > 0;

            if (intersect)
            {
                currentFramePairs.insert(pair);

                if (!alreadyActive)
                {
                    EventBattleSystem::Instance()->TriggerEvent(
                        rec_i.owner, hitboxA,
                        rec_j.owner, hitboxB);
                }
            }
        }
    }

    for (const auto& pair : activePairs)
    {
        if (currentFramePairs.count(pair) == 0)
        {
            /*EventBattleSystem::Instance()->TriggerExitEvent(
                pair.a, pair.hitboxA,
                pair.b, pair.hitboxB);*/
        }
    }

    activePairs = currentFramePairs;
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
        [=](const HitboxRecord& rec)
        {
            return rec.owner == owner &&
                rec.spine == data &&
                rec.boneName == bone_name &&
                rec.hitboxName == hitbox_name;
        });

    hitboxes.erase(it, hitboxes.end());
}

std::vector<sf::Vector2f> HopEngine::SpineTriggerSystem::getHitboxWorldVertices(
    spine::Skeleton* skeleton,
    spine::String slotName,
    spine::String attachmentName)
{
    std::vector<sf::Vector2f> result;

    if (!skeleton) return result;

    skeleton->updateWorldTransform();

    spine::Slot* slot = skeleton->findSlot(slotName);
    if (!slot) return result;

    spine::Attachment* attachment =
        skeleton->getAttachment(slot->getData().getIndex(), attachmentName);

    if (!attachment) return result;

    auto* bbox = dynamic_cast<spine::BoundingBoxAttachment*>(attachment);
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

    for (int i = 0; i < vertexCount; ++i)
    {
        result.emplace_back(
            worldVerts[i * 2],
            worldVerts[i * 2 + 1]);
    }

    return result;
}

HopEngine::Projection HopEngine::SpineTriggerSystem::projectPolygon(
    const std::vector<sf::Vector2f>& poly,
    const sf::Vector2f& axis)
{
    float dot = axis.x * poly[0].x + axis.y * poly[0].y;
    float min = dot, max = dot;

    for (size_t i = 1; i < poly.size(); ++i)
    {
        dot = axis.x * poly[i].x + axis.y * poly[i].y;
        min = std::min(min, dot);
        max = std::max(max, dot);
    }

    return { min, max };
}

bool HopEngine::SpineTriggerSystem::overlap(const Projection& p1, const Projection& p2)
{
    const float eps = 0.001f;
    return !(p1.max < p2.min - eps || p2.max < p1.min - eps);
}

sf::Vector2f HopEngine::SpineTriggerSystem::getNormal(
    const sf::Vector2f& p1,
    const sf::Vector2f& p2)
{
    sf::Vector2f edge = p2 - p1;
    return sf::Vector2f(-edge.y, edge.x);
}

void HopEngine::SpineTriggerSystem::Reset() {
    hitboxes.clear();
    activePairs.clear();
    currentFramePairs.clear();
}

bool HopEngine::SpineTriggerSystem::checkHitboxIntersectionSAT(
    const std::vector<sf::Vector2f>& a,
    const std::vector<sf::Vector2f>& b)
{
    if (a.size() < 3 || b.size() < 3)
        return false;

    auto testAxes = [&](const std::vector<sf::Vector2f>& poly1,
        const std::vector<sf::Vector2f>& poly2)
        {
            for (size_t i = 0; i < poly1.size(); ++i)
            {
                const auto& p1 = poly1[i];
                const auto& p2 = poly1[(i + 1) % poly1.size()];

                sf::Vector2f axis = getNormal(p1, p2);

                float len = std::sqrt(axis.x * axis.x + axis.y * axis.y);
                if (len < 1e-6f) continue;

                axis /= len;

                Projection proj1 = projectPolygon(poly1, axis);
                Projection proj2 = projectPolygon(poly2, axis);

                if (!overlap(proj1, proj2))
                    return false;
            }
            return true;
        };

    return testAxes(a, b) && testAxes(b, a);
}