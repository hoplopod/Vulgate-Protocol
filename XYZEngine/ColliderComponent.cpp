#include "pch.h"
#include "ColliderComponent.h"

namespace HopEngine
{
	ColliderComponent::ColliderComponent(GameObject* gameObject) : Component(gameObject) 
	{ 
		
	}

	void ColliderComponent::SetTrigger(bool newIsTrigger)
	{
		isTrigger = newIsTrigger;
	}

	void ColliderComponent::SetCollision(std::vector<int> vertical)
	{
		collision_vertical = vertical;
	}

	std::vector<int> ColliderComponent::GetCollision()
	{
		return collision_vertical;
	}

	void ColliderComponent::AddIgnoreCollision(ColliderComponent* addCollisionIgnore)
	{
		CollisionIgnore.push_back(addCollisionIgnore);
	}

	std::vector<ColliderComponent*> ColliderComponent::GetCollisionIgnore()
	{
		return CollisionIgnore;
	}

	void ColliderComponent::SubscribeHitBoxes(std::function<void(HitBox)> onHitBoxAction)
	{
		onHitBoxActions.push_back(onHitBoxAction);
	}
	void ColliderComponent::UnsubscribeHitBoxes(std::function<void(HitBox)> onHitBoxAction)
	{
		onHitBoxActions.erase(std::remove_if
		(
			onHitBoxActions.begin(),
			onHitBoxActions.end(),
			[&onHitBoxAction](const std::function<void(HitBox)>& action)
			{
				return action.target<void(HitBox)>() == onHitBoxAction.target<void(HitBox)>();
			}
		), onHitBoxActions.end());
	}

	void ColliderComponent::SubscribeTriggerEnter(std::function<void(Trigger)> onTriggerEnterAction)
	{
		onTriggerEnterActions.push_back(onTriggerEnterAction);
	}
	void ColliderComponent::UnsubscribeTriggerEnter(std::function<void(Trigger)> onTriggerEnterAction)
	{
		onTriggerEnterActions.erase(std::remove_if
		(
			onTriggerEnterActions.begin(),
			onTriggerEnterActions.end(),
			[&onTriggerEnterAction](const std::function<void(Trigger)>& action)
			{
				return action.target<void(Trigger)>() == onTriggerEnterAction.target<void(Trigger)>();
			}
		), onTriggerEnterActions.end());
	}

	void ColliderComponent::SubscribeTriggerExit(std::function<void(Trigger)> onTriggerExitAction)
	{
		onTriggerExitActions.push_back(onTriggerExitAction);
	}
	void ColliderComponent::UnsubscribeTriggerExit(std::function<void(Trigger)> onTriggerExitAction)
	{
		onTriggerExitActions.erase(std::remove_if
		(
			onTriggerExitActions.begin(),
			onTriggerExitActions.end(),
			[&onTriggerExitAction](const std::function<void(Trigger)>& action)
			{
				return action.target<void(Trigger)>() == onTriggerExitAction.target<void(Trigger)>();
			}
		), onTriggerExitActions.end());
	}

	void ColliderComponent::OnCollision(HitBox hitbox)
	{
		for (int i = 0; i < onHitBoxActions.size(); i++)
		{
			onHitBoxActions[i](hitbox);
		}
	}
	void ColliderComponent::OnTriggerEnter(Trigger trigger)
	{
		for (int i = 0; i < onTriggerEnterActions.size(); i++)
		{
			onTriggerEnterActions[i](trigger);
		}
	}
	void ColliderComponent::OnTriggerExit(Trigger trigger)
	{
		for (int i = 0; i < onTriggerExitActions.size(); i++)
		{
			onTriggerExitActions[i](trigger);
		}
	}
}