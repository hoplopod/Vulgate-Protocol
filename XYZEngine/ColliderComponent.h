#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include "Component.h"
#include "Collision.h"
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

		void SubscribeCollision(std::function<void(Collision)> onCollisionAction);
		void UnsubscribeCollision(std::function<void(Collision)> onCollisionAction);

		void SubscribeTriggerEnter(std::function<void(Trigger)> onTriggerEnterAction);
		void UnsubscribeTriggerEnter(std::function<void(Trigger)> onTriggerEnterAction);

		void SubscribeTriggerExit(std::function<void(Trigger)> onTriggerExitAction);
		void UnsubscribeTriggerExit(std::function<void(Trigger)> onTriggerExitAction);

		friend class TriggerSystem;

	protected:
		sf::FloatRect bounds;
		bool isTrigger = false;
		std::vector<int> collision_vertical = {0,0};

		void OnCollision(Collision collision);
		void OnTriggerEnter(Trigger trigger);
		void OnTriggerExit(Trigger trigger);

		std::vector<std::function<void(Collision)>> onCollisionActions;
		std::vector<std::function<void(Trigger)>> onTriggerEnterActions;
		std::vector<std::function<void(Trigger)>> onTriggerExitActions;
	};
}