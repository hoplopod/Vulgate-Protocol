#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include "Component.h"
#include "HitBoxes.h"
#include "MapCollision.h"
#include "Trigger.h"
#include "TriggersSystem.h"

namespace HopEngine
{
	class ColliderComponent : public Component
	{
	public:
		ColliderComponent(GameObject* gameObject);

		virtual void Update(float deltaTime) = 0;
		virtual void Render() = 0;

		void SetTrigger(bool newIsTrigger);
		
		void SetCollision(std::vector<int> vertical);
		std::vector<int> GetCollision();
		void AddIgnoreCollision(ColliderComponent* addCollisionIgnore);
		std::vector<ColliderComponent*> GetCollisionIgnore();

		void SubscribeHitBoxes(std::function<void(HitBox)> onHitBoxesAction);
		void UnsubscribeHitBoxes(std::function<void(HitBox)> onHitBoxesAction);

		void SubscribeTriggerEnter(std::function<void(Trigger)> onTriggerEnterAction);
		void UnsubscribeTriggerEnter(std::function<void(Trigger)> onTriggerEnterAction);

		void SubscribeTriggerExit(std::function<void(Trigger)> onTriggerExitAction);
		void UnsubscribeTriggerExit(std::function<void(Trigger)> onTriggerExitAction);

		friend class TriggerSystem;

	protected:
		sf::FloatRect bounds;
		sf::FloatRect map_bounds;
		bool isTrigger = false;
		std::vector<int> collision_vertical = {0,0};

		void OnCollision(HitBox collision);
		void OnTriggerEnter(Trigger trigger);
		void OnTriggerExit(Trigger trigger);

		std::vector<ColliderComponent*> CollisionIgnore;

		std::vector<std::function<void(HitBox)>> onHitBoxActions;
		std::vector<std::function<void(Trigger)>> onTriggerEnterActions;
		std::vector<std::function<void(Trigger)>> onTriggerExitActions;
	};
}