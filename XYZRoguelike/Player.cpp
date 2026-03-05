#include "Player.h"
#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>
#include <MovementComponent.h>
#include <SpriteDirectionComponent.h>
#include <SpriteMovementAnimationComponent.h>
#include <LayerRenderingComponent.h>
#include <SpineComponent.h>

namespace Roguelike
{
	Player::Player(const HopEngine::Vector2Df& position)
	{

		gameObject = HopEngine::GameWorld::Instance()->CreateGameObject("player");
		auto transform = gameObject->GetComponent<HopEngine::TransformComponent>();
		transform->SetWorldPosition(position);

		auto renderer = gameObject->AddComponent<HopEngine::SpriteRendererComponent>();

		auto camera = gameObject->AddComponent<HopEngine::CameraComponent>();
		camera->SetWindow(&HopEngine::RenderSystem::Instance()->GetMainWindow());
		camera->SetBaseResolution(1280, 720);
		camera->SetShift({ 150, 260.f });

		auto input = gameObject->AddComponent<HopEngine::InputComponent>();

		auto movement = gameObject->AddComponent<HopEngine::MovementComponent>();
		movement->SetSpeed(400.f);

		auto rigidbody = gameObject->AddComponent<HopEngine::RigidbodyComponent>();

		auto collider = gameObject->AddComponent<HopEngine::SpriteColliderComponent>();
		collider->AddToMapCollision();
		collider->SetMapCollision({ -10,0, 20, 10 });

		auto spine = gameObject->AddComponent<HopEngine::SpineComponent>();
		spine->SetData(HopEngine::ResourceSystem::Instance()->GetSkeletonData("player"));
		
	}

	HopEngine::GameObject* Player::GetGameObject()
	{
		return gameObject;
	}
}