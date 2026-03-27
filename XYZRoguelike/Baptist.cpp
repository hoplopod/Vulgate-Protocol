#include "Baptist.h"
#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>
#include <MovementComponent.h>
#include <SpriteDirectionComponent.h>
#include <SpriteMovementAnimationComponent.h>
#include <LayerRenderingComponent.h>

namespace Roguelike{

	Baptist::Baptist(const HopEngine::Vector2Df& position)
	{
		gameObject = HopEngine::GameWorld::Instance()->CreateGameObject("baptist");
		auto transform = gameObject->GetComponent<HopEngine::TransformComponent>();
		transform->SetWorldPosition(position);

		auto renderer = gameObject->AddComponent<HopEngine::SpriteRendererComponent>();

		auto rigidbody = gameObject->AddComponent<HopEngine::RigidbodyComponent>();

		auto collider = gameObject->AddComponent<HopEngine::SpriteColliderComponent>();
		collider->AddToMapCollision();
		collider->SetMapCollision({ -80, 0, 160, 10 });

		auto spine = gameObject->AddComponent<HopEngine::BaptistSpineComponent>();
		spine->SetData(HopEngine::ResourceSystem::Instance()->GetSkeletonData("baptist"));
		spine->setStartSkin("standart_right_direction");

		/*auto anim = new std::map<int, std::pair<spine::String, std::pair<int, bool>>>(std::move(createAnimations()));
		spine->AddAnimations(anim);*/

	}

	HopEngine::GameObject* Baptist::GetGameObject()
	{
		return gameObject;
	}

	std::map<int, std::pair<spine::String, std::pair<int, bool>>> Baptist::createAnimations()
	{
		std::map<int, std::pair<spine::String, std::pair<int, bool>>> animatioms;

		//animatioms.emplace(-2, std::make_pair(spine::String("plug (blade down)"), std::make_pair(2, false)));
		

		return animatioms;
	}

}