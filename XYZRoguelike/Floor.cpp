#include "Floor.h"
#include "LayerRenderingComponent.h"

Roguelike::Floor::Floor(const HopEngine::Vector2Df& position, int textureMapIndex)
{
	gameObject = HopEngine::GameWorld::Instance()->CreateGameObject("Floor");
	auto transform = gameObject->GetComponent<HopEngine::TransformComponent>();
	transform->SetWorldPosition(position);

	auto renderer = gameObject->AddComponent<HopEngine::SpriteRendererComponent>();
	renderer->SetTexture(*HopEngine::ResourceSystem::Instance()->GetTextureMapElementShared("level_floors", textureMapIndex));
	renderer->SetPixelSize(128, 128);
	HopEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<HopEngine::LayerRenderingComponent>()->AddToLayer(0, renderer);
}
