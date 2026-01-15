#include "Player.h"
#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>
#include <MovementComponent.h>
#include <SpriteDirectionComponent.h>
#include <SpriteMovementAnimationComponent.h>

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
		//Body
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("player_body");
		auto torso = gameObject->AddComponent<XYZEngine::BoneComponent>();
		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
		transform->SetWorldPosition(800,800);

		auto renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureMapElementShared("bone", 0));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f, 0);
		renderer->SetPixelSize(100, 100);
		//Arms
			//Right
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("player_right_upperArm");
		auto Right_upperArm = gameObject->AddComponent<XYZEngine::BoneComponent>();

		renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureMapElementShared("bone", 0));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f, 0);
		renderer->SetPixelSize(75, 50);
			//Lower Right
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("player_right_lowerArm");
		auto Right_lowerArm = gameObject->AddComponent<XYZEngine::BoneComponent>();

		renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureMapElementShared("bone", 0));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f, 0);
		renderer->SetPixelSize(75, 50);


		//Create skeleton
		
		torso->AddChild({ Right_upperArm, std::default_delete<XYZEngine::BoneComponent>()}, 0.f);
		Right_upperArm->GetGameObject()->GetComponent<XYZEngine::TransformComponent>()->SetParent(torso->GetGameObject()->GetComponent<XYZEngine::TransformComponent>());

		Right_upperArm->AddChild({ Right_lowerArm, std::default_delete<XYZEngine::BoneComponent>() }, 50.f);
		Right_lowerArm->GetGameObject()->GetComponent<XYZEngine::TransformComponent>()->SetParent(Right_upperArm->GetGameObject()->GetComponent<XYZEngine::TransformComponent>());

		Right_upperArm->GetGameObject()->GetComponent<XYZEngine::TransformComponent>()->SetLocalRotation(270);
		Right_lowerArm->GetGameObject()->GetComponent<XYZEngine::TransformComponent>()->SetLocalRotation(30);

	}

	XYZEngine::GameObject* Player::GetGameObject()
	{
		return gameObject;
	}
}