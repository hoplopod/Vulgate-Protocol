#pragma once

#include <map>
#include <vector>
#include "Vector.h"
#include "SpineComponent.h"

namespace HopEngine
{
    struct Projection { float min, max; };

    class SpineTriggerSystem
    {
    public:
        static SpineTriggerSystem* Instance();

        void Update();

        void Subscribe_HitBoxes(GameObject* owner, SpineComponent* data,
            spine::String bone_name, spine::String hitbox_name);
        void Unsubscribe_HitBoxes(GameObject* owner, SpineComponent* data,
            spine::String bone_name, spine::String hitbox_name);

        std::vector<sf::Vector2f> getHitboxWorldVertices(spine::Skeleton* skeleton,
            spine::String slotName,
            spine::String attachmentName);
        Projection projectPolygon(const std::vector<sf::Vector2f>& poly, const sf::Vector2f& axis);
        bool overlap(const Projection& p1, const Projection& p2);
        sf::Vector2f getNormal(const sf::Vector2f& p1, const sf::Vector2f& p2);
        bool checkHitboxIntersectionSAT(const std::vector<sf::Vector2f>& a,
            const std::vector<sf::Vector2f>& b);

    private:
        SpineTriggerSystem() = default;
        ~SpineTriggerSystem() = default;

        struct HitboxRecord
        {
            GameObject* owner;
            SpineComponent* spine;
            spine::String boneName;
            spine::String hitboxName;
        };
        std::vector<HitboxRecord> hitboxes;
        std::map<GameObject*, GameObject*> triggersEnteredPair;
    };
}