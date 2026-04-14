#pragma once

#include <map>
#include <iostream>
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "Vector.h"

namespace HopEngine
{
	class TriggerSystem
	{
	public:
		static TriggerSystem* Instance();

		void Update();

		float GetFixedDeltaTime() const;

		void Subscribe_Camera_HitBox(ColliderComponent* collider);
		void Unsubscribe_Camera_HitBox(ColliderComponent* collider);
		void Set_Camera_Box(ColliderComponent* collider);

		void Subscribe_HitBoxes(ColliderComponent* collider);
		void Unsubscribe_HitBoxes(ColliderComponent* collider);

		void Subscribe_Map_Collision(ColliderComponent* collider_for_a_map);
		void Unsubscribe_Map_Collision(ColliderComponent* collider_for_a_map);

		friend class GameWorld;
	private:
		TriggerSystem() {}
		~TriggerSystem() {}

		TriggerSystem(TriggerSystem const&) = delete;
		TriggerSystem& operator= (TriggerSystem const&) = delete;

		ColliderComponent* hitbox_for_camera;
		ColliderComponent* hitbox_of_camera;
		std::vector<ColliderComponent*> hitboxes;
		std::vector<ColliderComponent*> colliders_for_a_map;
		std::map<ColliderComponent*, ColliderComponent*> triggersEnteredPair;

		float fixedDeltaTime = 0.02f;
	};
}