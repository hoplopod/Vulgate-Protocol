#include "Player.h"
#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>
#include <MovementComponent.h>
#include <SpriteDirectionComponent.h>
#include <SpriteMovementAnimationComponent.h>
#include <LayerRenderingComponent.h>

namespace XYZRoguelike
{
	Player::Player(const XYZEngine::Vector2Df& position)
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Player");
		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
		transform->SetWorldPosition(position);

		auto renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureMapElementShared("player", 0));
		renderer->SetPixelSize(100, 100);
		XYZEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<XYZEngine::LayerRenderingComponent>()->AddToLayer(1, renderer);

		auto camera = gameObject->AddComponent<XYZEngine::CameraComponent>();
		camera->SetWindow(&XYZEngine::RenderSystem::Instance()->GetMainWindow());
		camera->SetBaseResolution(1280, 720);

		auto input = gameObject->AddComponent<XYZEngine::InputComponent>();

		auto movement = gameObject->AddComponent<XYZEngine::MovementComponent>();
		movement->SetSpeed(400.f);

		auto spriteDirection = gameObject->AddComponent<XYZEngine::SpriteDirectionComponent>();

		auto rigidbody = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();
		rigidbody->SetKinematic(false);

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();

		auto animator = gameObject->AddComponent<XYZEngine::SpriteMovementAnimationComponent>();
		animator->Initialize("player", 6.f);

		createSkeleton();
	}

	void Player::createSkeleton()
	{
		float player_scale = 3.f;

		//Head
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Player_head");
		auto head = gameObject->AddComponent<XYZEngine::BoneComponent>();

		auto renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureCopy("player_head"));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f - 4, renderer->GetSprite()->getTexture()->getSize().y-12.f);
		renderer->SetPixelSize(32*player_scale, 32*player_scale);
		XYZEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<XYZEngine::LayerRenderingComponent>()->AddToLayer(3, renderer);

		//Body
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Player_body");
		auto body = gameObject->AddComponent<XYZEngine::BoneComponent>();
		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
		transform->SetWorldPosition(800,800);

		renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureCopy("player_body"));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f, 0);
		renderer->SetPixelSize(64 * player_scale, 64 * player_scale);
		XYZEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<XYZEngine::LayerRenderingComponent>()->AddToLayer(2, renderer);

		//Arms
		//left
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Player_shoulder_left");
		auto player_shoulder_left = gameObject->AddComponent<XYZEngine::BoneComponent>();

		renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureCopy("player_shoulder_left_back"));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f, 2);
		renderer->SetPixelSize(32 * player_scale, 32 * player_scale);
		XYZEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<XYZEngine::LayerRenderingComponent>()->AddToLayer(1, renderer);

		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Player_forearm_left");
		auto player_forearm_left = gameObject->AddComponent<XYZEngine::BoneComponent>();

		renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureCopy("player_forearm_left_back"));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f - 1, 5);
		renderer->SetPixelSize(32 * player_scale, 32 * player_scale);
		XYZEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<XYZEngine::LayerRenderingComponent>()->AddToLayer(1, renderer);

		//Create skeleton

		body->AddChild({ head, std::default_delete<XYZEngine::BoneComponent>() }, 0.f, 0.f);
		
		body->AddChild({ player_shoulder_left, std::default_delete<XYZEngine::BoneComponent>()}, 33.f, 46);

		player_shoulder_left->AddChild({ player_forearm_left, std::default_delete<XYZEngine::BoneComponent>() }, 32 * player_scale - 2, 0);

		
		player_shoulder_left->GetGameObject()->GetComponent<XYZEngine::TransformComponent>()->SetLocalRotation(30);
		player_forearm_left->GetGameObject()->GetComponent<XYZEngine::TransformComponent>()->SetLocalRotation(60);
		head->GetGameObject()->GetComponent<XYZEngine::TransformComponent>()->SetLocalRotation(60);
	}

	XYZEngine::GameObject* Player::GetGameObject()
	{
		return gameObject;
	}
}