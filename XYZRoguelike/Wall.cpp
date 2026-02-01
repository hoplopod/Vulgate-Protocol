#include "Wall.h"
#include <SpriteMovementAnimationComponent.h>
#include <LayerRenderingComponent.h>
#include <SpriteColliderComponent.h>

Roguelike::Wall::Wall(const HopEngine::Vector2Df position, int textureMapIndex)
{
	gameObject = HopEngine::GameWorld::Instance()->CreateGameObject("Wall");
	auto transform = gameObject->GetComponent<HopEngine::TransformComponent>();
	transform->SetWorldPosition(position);

	auto renderer = gameObject->AddComponent<HopEngine::SpriteRendererComponent>();
	renderer->SetTexture(*HopEngine::ResourceSystem::Instance()->GetTextureMapElementShared("level_walls", textureMapIndex));
	renderer->SetPixelSize(128, 128);
	HopEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<HopEngine::LayerRenderingComponent>()->AddToLayer(0, renderer);

	auto rigidbody = gameObject->AddComponent<HopEngine::RigidbodyComponent>();
	rigidbody->SetKinematic(true);

	auto collider = gameObject->AddComponent<HopEngine::SpriteColliderComponent>();
}
