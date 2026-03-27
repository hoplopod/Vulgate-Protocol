#include "pch.h"
#include "TriggersSystem.h"
#include "CameraComponent.h"

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
		

		//Collision with a map
		for (int i = 0; i < colliders_for_a_map.size(); i++) {

			int collisionX = 0;
			int collisionY = 0;

			for (int j = 0; j < hitboxes.size(); j++)
			{
				auto body = hitboxes[j]->GetGameObject()->GetComponent<RigidbodyComponent>();
				if (!body->GetKinematic())
				{
					continue;
				}
				
				sf::FloatRect intersection;
				if (colliders_for_a_map[i]->map_bounds.intersects(hitboxes[j]->bounds, intersection))
				{
					float intersectionWidth = intersection.width;
					float intersectionHeight = intersection.height;
					Vector2Df intersectionPosition = { intersection.left - 0.5f * intersectionWidth, intersection.top - 0.5f * intersectionHeight };

					Vector2Df aPosition = { colliders_for_a_map[i]->map_bounds.left, colliders_for_a_map[i]->map_bounds.top };
					auto aTransform = colliders_for_a_map[i]->GetGameObject()->GetComponent<TransformComponent>();

					if (intersectionWidth > intersectionHeight)
					{
						if (intersectionPosition.y > aPosition.y)
						{
							if (abs(intersectionPosition.y - aPosition.y) > ERROR_RATE) collisionY = 1;
							//aTransform->MoveBy({ 0, -intersectionHeight });

							//std::cout << "Top collision" << std::endl;
						}
						else
						{
							if (abs(intersectionPosition.y - aPosition.y) <= ERROR_RATE) collisionY = -1;
							//aTransform->MoveBy({ 0, intersectionHeight });

							//std::cout << "Down collision" << std::endl;
						}
					}
					else
					{
						if (intersectionPosition.x > aPosition.x)
						{
							if (abs(intersectionPosition.x - aPosition.x) > ERROR_RATE) collisionX = -1;
							else aTransform->MoveBy({ -intersectionWidth, 0 });

							//std::cout << "Right collision" << std::endl;
						}
						else
						{
							if (abs(intersectionPosition.x - aPosition.x) <= ERROR_RATE) collisionX = 1;
							else aTransform->MoveBy({ intersectionWidth, 0 });

							//std::cout << "Left collision" << std::endl;
						}
					}

				}
			}
			colliders_for_a_map[i]->SetCollision({ collisionX, collisionY });
		}

		//Collision with the camera

		float deltaTime = fixedDeltaTime; // врем€ между кадрами в секундах

		auto for_camera_transform = hitbox_for_camera->GetGameObject()->GetComponent<TransformComponent>();
		auto of_camera_transform = hitbox_of_camera->GetGameObject()->GetComponent<TransformComponent>();

		float playerX = for_camera_transform->GetWorldPosition().x;
		float cameraX = of_camera_transform->GetWorldPosition().x;
		float cameraWidth = hitbox_of_camera->map_bounds.width;

		float cameraLeft = cameraX - cameraWidth / 2.f;
		float cameraRight = cameraX + cameraWidth / 2.f;

		float deadZoneLeftOffset = 50.f;
		float deadZoneRightOffset = 50.f;

		float deadZoneMin = cameraLeft + deadZoneLeftOffset;
		float deadZoneMax = cameraRight - deadZoneRightOffset;

		// √истерезис (увеличил до 5, можно подстроить)
		const float hysteresis = 5.f;

		float shiftX = 0.f;
		float targetCameraX = cameraX; // целева€ позици€ центра камеры

		if (playerX < deadZoneMin - hysteresis) {
			targetCameraX += playerX - (deadZoneMin - hysteresis);
		}
		else if (playerX > deadZoneMax + hysteresis) {
			targetCameraX += playerX - (deadZoneMax + hysteresis);
		}
		else {
			// ≈сли игрок внутри dead zone с учЄтом гистерезиса, камера не должна стремитьс€ к цели,
			// чтобы не было "подт€гивани€". Ќо если нужно, чтобы камера плавно возвращалась,
			// можно оставить targetCameraX = cameraX.
			targetCameraX = cameraX;
		}

		// ¬ычисл€ем разницу
		float diff = targetCameraX - cameraX;

		// ѕараметры плавности и скорости
		const float maxSpeed = 1500.f; // пикселей в секунду
		const float smoothTime = 0.05f; // секунд, за которое камера преодолевает отставание (только дл€ lerp)

		// ќграничиваем максимальное смещение за кадр по скорости
		float maxDelta = maxSpeed * deltaTime;
		if (std::abs(diff) > maxDelta) {
			diff = (diff > 0 ? maxDelta : -maxDelta);
		}

		// ѕримен€ем lerp с адаптивным коэффициентом (чтобы камера не "залипала")
		// ≈сли diff маленький, можно двигать мгновенно, чтобы не было длительного доведени€.
		if (std::abs(diff) > 0.1f) {
			//  оэффициент lerp, завис€щий от времени (чтобы камера всегда догон€ла за smoothTime)
			float smooth = 1.f - exp(-deltaTime / smoothTime);
			cameraX += diff * smooth;
		}
		else {
			// ≈сли разница мала, сразу ставим целевую позицию, чтобы избежать микродвижений
			cameraX = targetCameraX;
		}

		of_camera_transform->SetWorldPosition(cameraX, of_camera_transform->GetWorldPosition().y);

		//Triggers
		for (int i = 0; i < hitboxes.size(); i++)
		{
			auto body = hitboxes[i]->GetGameObject()->GetComponent<RigidbodyComponent>();
			if (body->GetKinematic())
			{
				continue;
			}

			for (int j = 0; j < hitboxes.size(); j++)
			{
				if (j == i)
				{
					continue;
				}

				/*bool ignore = false;
				for (int l = 0; l < hitboxes[i]->GetCollisionIgnore().size(); ++l) {
					if (hitboxes[i]->GetCollisionIgnore()[l] == hitboxes[j]) {
						ignore = true;
						break;
					}
				}
				if (ignore) continue;*/

				sf::FloatRect intersection;
				if (hitboxes[i]->bounds.intersects(hitboxes[j]->bounds, intersection))
				{
					if (hitboxes[i]->isTrigger != hitboxes[j]->isTrigger)
					{
						if (triggersEnteredPair.find(hitboxes[i]) == triggersEnteredPair.end() && triggersEnteredPair.find(hitboxes[j]) == triggersEnteredPair.end())
						{
							auto trigger = new Trigger(hitboxes[i], hitboxes[j]);
							hitboxes[i]->OnTriggerEnter(*trigger);
							hitboxes[j]->OnTriggerEnter(*trigger);

							triggersEnteredPair.emplace(hitboxes[i], hitboxes[j]);
						}
					}
				}
				/*else {
					CollisionActions.push_back(colliders_for_a_map[i]);

					auto collision = new Collision(colliders_for_a_map[i], hitboxes[j], intersection);
					hitboxes[i]->OnCollision(*collision);
					hitboxes[j]->OnCollision(*collision);
					for (int k = 0; k < CollisionActions.size(); ++k) {
						if (CollisionActions[k] == hitboxes[j]) CollisionActions.erase(std::remove(CollisionActions.begin(), CollisionActions.end(), hitboxes[j]), CollisionActions.end());
					}
				}*/
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
	}

	void TriggerSystem::Subscribe_HitBoxes(ColliderComponent* collider)
	{
		std::cout << "Subscribe " << collider << std::endl;
		hitboxes.push_back(collider);
	}
	void TriggerSystem::Unsubscribe_HitBoxes(ColliderComponent* collider)
	{
		std::cout << "Unsubscribe " << collider << std::endl;

		hitboxes.erase(std::remove_if(hitboxes.begin(), hitboxes.end(), [collider](ColliderComponent* obj) 
			{ return obj == collider; }), hitboxes.end());
	}

	void TriggerSystem::Subscribe_Map_Collision(ColliderComponent* collider_for_a_map)
	{
		std::cout << "Subscribe " << collider_for_a_map << std::endl;
		colliders_for_a_map.push_back(collider_for_a_map);
	}
	void TriggerSystem::Unsubscribe_Map_Collision(ColliderComponent* collider_for_a_map)
	{
		std::cout << "Unsubscribe " << collider_for_a_map << std::endl;

		colliders_for_a_map.erase(std::remove_if(colliders_for_a_map.begin(), colliders_for_a_map.end(), [collider_for_a_map](ColliderComponent* obj) 
			{ return obj == collider_for_a_map; }), colliders_for_a_map.end());
	}
	
	void TriggerSystem::Subscribe_Camera_HitBox(ColliderComponent* collider)
	{
		std::cout << "Subscribe " << collider << std::endl;
		hitbox_for_camera = collider;
	}
	void TriggerSystem::Unsubscribe_Camera_HitBox(ColliderComponent* collider)
	{
		std::cout << "Unsubscribe " << collider << std::endl;
		hitbox_for_camera = nullptr;
	}
	void TriggerSystem::Set_Camera_Box(ColliderComponent* collider)
	{
		hitbox_of_camera = collider;
	}
}