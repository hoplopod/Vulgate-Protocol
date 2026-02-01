#include "pch.h"
#include "TriggersSystem.h"

const float ERROR_RATE = 7.f;

namespace HopEngine
{
	TriggerSystem* TriggerSystem::Instance()
	{
		static TriggerSystem TriggersSystem;
		return &TriggersSystem;
	}

	float TriggerSystem::GetFixedDeltaTime() const
	{
		return fixedDeltaTime;
	}

	void TriggerSystem::Update()
	{
		for (int i = 0; i < colliders.size(); i++)
		{
			auto body = colliders[i]->GetGameObject()->GetComponent<RigidbodyComponent>();
			if (body->GetKinematic())
			{
				continue;
			}
			int collisionX = 0;
			int collisionY = 0;

			for (int j = 0; j < colliders.size(); j++)
			{
				if (j == i)
				{
					continue;
				}

				bool ignore = false;
				for (int l = 0; l < colliders[i]->GetCollisionIgnore().size(); ++l) {
					if (colliders[i]->GetCollisionIgnore()[l] == colliders[j]) {
						ignore = true;
						break;
					}
				}
				if (ignore) continue;

				sf::FloatRect intersection;
				if (colliders[i]->bounds.intersects(colliders[j]->bounds, intersection))
				{
					if (colliders[i]->isTrigger != colliders[j]->isTrigger)
					{
						if (triggersEnteredPair.find(colliders[i]) == triggersEnteredPair.end() && triggersEnteredPair.find(colliders[j]) == triggersEnteredPair.end())
						{
							auto trigger = new Trigger(colliders[i], colliders[j]);
							colliders[i]->OnTriggerEnter(*trigger);
							colliders[j]->OnTriggerEnter(*trigger);

							triggersEnteredPair.emplace(colliders[i], colliders[j]);
						}
					}
					else if (!colliders[i]->isTrigger)
					{

						float intersectionWidth = intersection.width;
						float intersectionHeight = intersection.height;
						Vector2Df intersectionPosition = { intersection.left - 0.5f * intersectionWidth, intersection.top - 0.5f * intersectionHeight };

						Vector2Df aPosition = { colliders[i]->bounds.left,  colliders[i]->bounds.top };
						auto aTransform = colliders[i]->GetGameObject()->GetComponent<TransformComponent>();

						if (intersectionWidth > intersectionHeight)
						{
							if (intersectionPosition.y > aPosition.y)
							{
								if (abs(intersectionPosition.y - aPosition.y) > ERROR_RATE) collisionY = -1;
								else aTransform->MoveBy({ 0, -intersectionHeight });

								std::cout << "Top collision" << std::endl;
							}
							else
							{
								if (abs(intersectionPosition.y - aPosition.y) <= ERROR_RATE) collisionY = 1;
								else aTransform->MoveBy({ 0, intersectionHeight });

								std::cout << "Down collision" << std::endl;
							}
						}
						else
						{
							if (intersectionPosition.x > aPosition.x)
							{
								if (abs(intersectionPosition.x - aPosition.x) > ERROR_RATE) collisionX = -1;
								else aTransform->MoveBy({ -intersectionWidth, 0 });

								std::cout << "Right collision" << std::endl;
							}
							else
							{
								if (abs(intersectionPosition.x - aPosition.x) <= ERROR_RATE) collisionX = 1;
								else aTransform->MoveBy({ intersectionWidth, 0 });

								std::cout << "Left collision" << std::endl;
							}
						}
						CollisionActions.push_back(colliders[j]);

						auto collision = new Collision(colliders[i], colliders[j], intersection);
						colliders[i]->OnCollision(*collision);
						colliders[j]->OnCollision(*collision);
					}
				}
				else {
					for (int k = 0; k < CollisionActions.size(); ++k) {
						if (CollisionActions[k] == colliders[j]) CollisionActions.erase(std::remove(CollisionActions.begin(), CollisionActions.end(), colliders[j]), CollisionActions.end());
					}
				}
			}
			colliders[i]->SetCollision({ collisionX, collisionY });
			if (CollisionActions.empty()) colliders[i]->SetCollision({ 0, 0 });
		}


		for (auto triggeredPair = triggersEnteredPair.cbegin(), nextTriggeredPair = triggeredPair; triggeredPair != triggersEnteredPair.cend(); triggeredPair = nextTriggeredPair)
		{
			++nextTriggeredPair;
			if (!triggeredPair->first->bounds.intersects(triggeredPair->second->bounds))
			{
				auto trigger = new Trigger(triggeredPair->first, triggeredPair->second);
				triggeredPair->first->OnTriggerExit(*trigger);
				triggeredPair->second->OnTriggerExit(*trigger);

				triggersEnteredPair.erase(triggeredPair);
			}
		}
	}

	void TriggerSystem::Subscribe(ColliderComponent* collider)
	{
		std::cout << "Subscribe " << collider << std::endl;
		colliders.push_back(collider);
	}
	void TriggerSystem::Unsubscribe(ColliderComponent* collider)
	{
		std::cout << "Unsubscribe " << collider << std::endl;

		colliders.erase(std::remove_if(colliders.begin(), colliders.end(), [collider](ColliderComponent* obj) { return obj == collider; }), colliders.end());
	}
}