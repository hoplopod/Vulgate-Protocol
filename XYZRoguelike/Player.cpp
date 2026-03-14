#include "Player.h"
#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>
#include <MovementComponent.h>
#include <SpriteDirectionComponent.h>
#include <SpriteMovementAnimationComponent.h>
#include <LayerRenderingComponent.h>


namespace Roguelike
{
	Player::Player(const HopEngine::Vector2Df& position)
	{

		gameObject = HopEngine::GameWorld::Instance()->CreateGameObject("player");
		auto transform = gameObject->GetComponent<HopEngine::TransformComponent>();
		transform->SetWorldPosition(position);

		auto input = gameObject->AddComponent<HopEngine::InputComponent>();

		auto spine = gameObject->AddComponent<HopEngine::PlayerSpineComponent>();
		spine->SetData(HopEngine::ResourceSystem::Instance()->GetSkeletonData("player"));
		spine->setStartSkin("standart_left_direction");

		auto anim = new std::map<int, std::pair<spine::String, std::pair<int, bool>>>(std::move(createAnimations())); 
		spine->AddAnimations(anim);

		auto renderer = gameObject->AddComponent<HopEngine::SpriteRendererComponent>();

		auto camera = gameObject->AddComponent<HopEngine::CameraComponent>();
		camera->SetWindow(&HopEngine::RenderSystem::Instance()->GetMainWindow());
		camera->SetBaseResolution(1280, 720);
		camera->SetShift({ 150, 260.f });

		auto movement = gameObject->AddComponent<HopEngine::MovementComponent>();
		movement->SetSpeed(400.f);

		auto rigidbody = gameObject->AddComponent<HopEngine::RigidbodyComponent>();

		auto collider = gameObject->AddComponent<HopEngine::SpriteColliderComponent>();
		collider->AddToMapCollision();
		collider->SetMapCollision({ -10,0, 20, 10 });

	}

	HopEngine::GameObject* Player::GetGameObject()
	{
		return gameObject;
	}

	std::map<int, std::pair<spine::String, std::pair<int, bool>>> Player::createAnimations()
	{
		std::map<int, std::pair<spine::String, std::pair<int, bool>>> animatioms;
		int num = 1;

		animatioms.emplace(num, std::make_pair(spine::String("Stable"), std::make_pair(0, true))); num++;
		animatioms.emplace(num, std::make_pair(spine::String("walk (test)"), std::make_pair(0, true))); num++;

		return animatioms;
	}
}
