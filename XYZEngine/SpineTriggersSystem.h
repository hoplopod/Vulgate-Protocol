#pragma once

#include <map>
#include <cmath>
#include <iostream>
#include <algorithm>
#include "Vector.h"
#include "SpineComponent.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"

namespace HopEngine
{
	struct Projection {
	float min, max;
	};

	class SpineTriggerSystem
	{
	public:
		static SpineTriggerSystem* Instance();

		void Update();

		void Subscribe_HitBoxes(ColliderComponent* new_collider, SpineComponent* data, spine::String bone_name, spine::String hitbox_name);
		void Unsubscribe_HitBoxes(ColliderComponent* new_collider, SpineComponent* data, spine::String bone_name, spine::String hitbox_name);

		std::vector<sf::Vector2f> getHitboxWorldVertices(spine::Skeleton* skeleton, spine::String boneName, spine::String attachmentName);

		Projection projectPolygon(const std::vector<sf::Vector2f>& poly, const sf::Vector2f& axis);
		bool overlap(const Projection& p1, const Projection& p2);
		sf::Vector2f getNormal(const sf::Vector2f& p1, const sf::Vector2f& p2);

		bool checkHitboxIntersectionSAT(const std::vector<sf::Vector2f>& a, const std::vector<sf::Vector2f>& b);

	private:
		SpineTriggerSystem() {}
		~SpineTriggerSystem() {}

		SpineTriggerSystem(SpineTriggerSystem const&) = delete;
		SpineTriggerSystem& operator= (SpineTriggerSystem const&) = delete;

		std::vector<std::pair<SpineComponent*, std::pair<spine::String, spine::String>>> hitboxes;
		std::vector<ColliderComponent*> collider;
		std::map<ColliderComponent*, ColliderComponent*> triggersEnteredPair;

	};
}
