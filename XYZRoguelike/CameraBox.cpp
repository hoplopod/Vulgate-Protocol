#include "CameraBox.h"
#include "SpriteColliderComponent.h"
#include "TriggersSystem.h"

Roguelike::CameraBox::CameraBox(const HopEngine::Vector2Df& position)
{
	gameObject = HopEngine::GameWorld::Instance()->CreateGameObject("camera_box");
	auto transform = gameObject->GetComponent<HopEngine::TransformComponent>();
	transform->SetWorldPosition(position);

	auto renderer = gameObject->AddComponent<HopEngine::SpriteRendererComponent>();

	auto rigidbody = gameObject->AddComponent<HopEngine::RigidbodyComponent>();

	auto collider = gameObject->AddComponent<HopEngine::SpriteColliderComponent>();
	//collider->AddToMapCollision();
	collider->SetMapCollision({ -250, 0, 500, 10 });
	HopEngine::TriggerSystem::Instance()->Set_Camera_Box(collider);
	
	auto camera = gameObject->AddComponent<HopEngine::CameraComponent>();
	camera->SetWindow(&HopEngine::RenderSystem::Instance()->GetMainWindow());
	camera->SetBaseResolution(1280, 720);
	camera->SetShift({ 0, 260.f });
}