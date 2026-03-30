#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include "Component.h"
#include "Trigger.h"
#include "TriggersSystem.h"
#include "SpineTriggersSystem.h"

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

		void SubscribeTriggerEnter(std::function<void(Trigger)> onTriggerEnterAction);
		void UnsubscribeTriggerEnter(std::function<void(Trigger)> onTriggerEnterAction);

		void SubscribeTriggerExit(std::function<void(Trigger)> onTriggerExitAction);
		void UnsubscribeTriggerExit(std::function<void(Trigger)> onTriggerExitAction);

		friend class TriggerSystem;
		friend class SpineTriggerSystem;

	protected:
		sf::FloatRect bounds;
		sf::FloatRect map_bounds;
		bool isTrigger = false;
		std::vector<int> collision_vertical = {0,0};
		std::vector<sf::Vector2f> spine_hitbox;

		void OnTriggerEnter(Trigger trigger);
		void OnTriggerExit(Trigger trigger);

		std::vector<ColliderComponent*> CollisionIgnore;

		std::vector<std::function<void(Trigger)>> onTriggerEnterActions;
		std::vector<std::function<void(Trigger)>> onTriggerExitActions;
	};
}