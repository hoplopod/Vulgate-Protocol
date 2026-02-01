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
		void Subscribe(ColliderComponent* collider);
		void Unsubscribe(ColliderComponent* collider);
	private:
		TriggerSystem() {}
		~TriggerSystem() {}

		TriggerSystem(TriggerSystem const&) = delete;
		TriggerSystem& operator= (TriggerSystem const&) = delete;

		std::vector<ColliderComponent*> colliders;
		std::map<ColliderComponent*, ColliderComponent*> triggersEnteredPair;

		float fixedDeltaTime = 0.02f;

		std::vector<ColliderComponent*> CollisionActions;
	};
}