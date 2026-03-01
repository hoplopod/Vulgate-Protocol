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
		//createSkeleton();

		gameObject = HopEngine::GameWorld::Instance()->CreateGameObject("player");
		auto transform = gameObject->GetComponent<HopEngine::TransformComponent>();
		transform->SetWorldPosition(position);

		auto renderer = gameObject->AddComponent<HopEngine::SpriteRendererComponent>();

		auto camera = gameObject->AddComponent<HopEngine::CameraComponent>();
		camera->SetWindow(&HopEngine::RenderSystem::Instance()->GetMainWindow());
		camera->SetBaseResolution(1280, 720);
		camera->SetShift({ 100, 260.f });

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

	void Player::createSkeleton()
	{
		float player_scale = 3.f;
		std::vector<HopEngine::SpriteColliderComponent*> colliders;

		//Head
		gameObject = HopEngine::GameWorld::Instance()->CreateGameObject("Player_head");
		auto head = gameObject->AddComponent<HopEngine::BoneComponent>();
		auto renderer = gameObject->AddComponent<HopEngine::SpriteRendererComponent>();
		renderer->SetTexture(*HopEngine::ResourceSystem::Instance()->GetTextureCopy("player_head"));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f - 2, renderer->GetSprite()->getTexture()->getSize().y - 7);
		renderer->SetPixelSize(renderer->GetSprite()->getTexture()->getSize().x * player_scale, renderer->GetSprite()->getTexture()->getSize().y * player_scale);
		HopEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<HopEngine::LayerRenderingComponent>()->AddToLayer(3, renderer);
		gameObject->AddComponent<HopEngine::RigidbodyComponent>();
		colliders.push_back(gameObject->AddComponent<HopEngine::SpriteColliderComponent>());

		//Legs
		//left
		gameObject = HopEngine::GameWorld::Instance()->CreateGameObject("Player_hip_left");
		auto player_hip_left = gameObject->AddComponent<HopEngine::BoneComponent>();
		renderer = gameObject->AddComponent<HopEngine::SpriteRendererComponent>();
		renderer->SetTexture(*HopEngine::ResourceSystem::Instance()->GetTextureCopy("player_hip_back"));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f + 1, 5.f);
		renderer->SetPixelSize(renderer->GetSprite()->getTexture()->getSize().x * player_scale, renderer->GetSprite()->getTexture()->getSize().y * player_scale);
		HopEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<HopEngine::LayerRenderingComponent>()->AddToLayer(1, renderer);
		gameObject->AddComponent<HopEngine::RigidbodyComponent>();
		colliders.push_back(gameObject->AddComponent<HopEngine::SpriteColliderComponent>());

		gameObject = HopEngine::GameWorld::Instance()->CreateGameObject("Player_shin_left");
		auto player_shin_left = gameObject->AddComponent<HopEngine::BoneComponent>();
		renderer = gameObject->AddComponent<HopEngine::SpriteRendererComponent>();
		renderer->SetTexture(*HopEngine::ResourceSystem::Instance()->GetTextureCopy("player_shin_back"));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f + 3, 4);
		renderer->SetPixelSize(renderer->GetSprite()->getTexture()->getSize().x * player_scale, renderer->GetSprite()->getTexture()->getSize().y * player_scale);
		HopEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<HopEngine::LayerRenderingComponent>()->AddToLayer(1, renderer);
		gameObject->AddComponent<HopEngine::RigidbodyComponent>();
		colliders.push_back(gameObject->AddComponent<HopEngine::SpriteColliderComponent>());

		gameObject = HopEngine::GameWorld::Instance()->CreateGameObject("Player_foot_left");
		auto player_foot_left = gameObject->AddComponent<HopEngine::BoneComponent>();
		renderer = gameObject->AddComponent<HopEngine::SpriteRendererComponent>();
		renderer->SetTexture(*HopEngine::ResourceSystem::Instance()->GetTextureCopy("player_foot_back"));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f - 4, 2);
		renderer->SetPixelSize(renderer->GetSprite()->getTexture()->getSize().x * player_scale, renderer->GetSprite()->getTexture()->getSize().y * player_scale);
		HopEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<HopEngine::LayerRenderingComponent>()->AddToLayer(1, renderer);
		gameObject->AddComponent<HopEngine::RigidbodyComponent>();
		colliders.push_back(gameObject->AddComponent<HopEngine::SpriteColliderComponent>());

		//right
		gameObject = HopEngine::GameWorld::Instance()->CreateGameObject("Player_hip_right");
		auto player_hip_right = gameObject->AddComponent<HopEngine::BoneComponent>();
		renderer = gameObject->AddComponent<HopEngine::SpriteRendererComponent>();
		renderer->SetTexture(*HopEngine::ResourceSystem::Instance()->GetTextureCopy("player_hip_front"));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f + 1, 5.f);
		renderer->SetPixelSize(renderer->GetSprite()->getTexture()->getSize().x* player_scale, renderer->GetSprite()->getTexture()->getSize().y* player_scale);
		HopEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<HopEngine::LayerRenderingComponent>()->AddToLayer(3, renderer);
		gameObject->AddComponent<HopEngine::RigidbodyComponent>();
		colliders.push_back(gameObject->AddComponent<HopEngine::SpriteColliderComponent>());

		gameObject = HopEngine::GameWorld::Instance()->CreateGameObject("Player_shin_right");
		auto player_shin_right = gameObject->AddComponent<HopEngine::BoneComponent>();
		renderer = gameObject->AddComponent<HopEngine::SpriteRendererComponent>();
		renderer->SetTexture(*HopEngine::ResourceSystem::Instance()->GetTextureCopy("player_shin_front"));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f + 3, 4);
		renderer->SetPixelSize(renderer->GetSprite()->getTexture()->getSize().x* player_scale, renderer->GetSprite()->getTexture()->getSize().y* player_scale);
		HopEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<HopEngine::LayerRenderingComponent>()->AddToLayer(3, renderer);
		gameObject->AddComponent<HopEngine::RigidbodyComponent>();
		colliders.push_back(gameObject->AddComponent<HopEngine::SpriteColliderComponent>());

		gameObject = HopEngine::GameWorld::Instance()->CreateGameObject("Player_foot_right");
		auto player_foot_right = gameObject->AddComponent<HopEngine::BoneComponent>();
		renderer = gameObject->AddComponent<HopEngine::SpriteRendererComponent>();
		renderer->SetTexture(*HopEngine::ResourceSystem::Instance()->GetTextureCopy("player_foot_front"));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f - 4, 2);
		renderer->SetPixelSize(renderer->GetSprite()->getTexture()->getSize().x* player_scale, renderer->GetSprite()->getTexture()->getSize().y* player_scale);
		HopEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<HopEngine::LayerRenderingComponent>()->AddToLayer(3, renderer);
		gameObject->AddComponent<HopEngine::RigidbodyComponent>();
		colliders.push_back(gameObject->AddComponent<HopEngine::SpriteColliderComponent>());

		//Arms
		//left
		gameObject = HopEngine::GameWorld::Instance()->CreateGameObject("Player_shoulder_left");
		auto player_shoulder_left = gameObject->AddComponent<HopEngine::BoneComponent>();
		renderer = gameObject->AddComponent<HopEngine::SpriteRendererComponent>();
		renderer->SetTexture(*HopEngine::ResourceSystem::Instance()->GetTextureCopy("player_shoulder_left_back"));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f, 5.f);
		renderer->SetPixelSize(renderer->GetSprite()->getTexture()->getSize().x * player_scale, renderer->GetSprite()->getTexture()->getSize().y * player_scale);
		HopEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<HopEngine::LayerRenderingComponent>()->AddToLayer(1, renderer);
		gameObject->AddComponent<HopEngine::RigidbodyComponent>();
		colliders.push_back(gameObject->AddComponent<HopEngine::SpriteColliderComponent>());

		gameObject = HopEngine::GameWorld::Instance()->CreateGameObject("Player_forearm_left");
		auto player_forearm_left = gameObject->AddComponent<HopEngine::BoneComponent>();
		renderer = gameObject->AddComponent<HopEngine::SpriteRendererComponent>();
		renderer->SetTexture(*HopEngine::ResourceSystem::Instance()->GetTextureCopy("player_forearm_left_back"));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f+1,4);
		renderer->SetPixelSize(renderer->GetSprite()->getTexture()->getSize().x * player_scale, renderer->GetSprite()->getTexture()->getSize().y * player_scale);
		HopEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<HopEngine::LayerRenderingComponent>()->AddToLayer(1, renderer);
		gameObject->AddComponent<HopEngine::RigidbodyComponent>();
		colliders.push_back(gameObject->AddComponent<HopEngine::SpriteColliderComponent>());

		gameObject = HopEngine::GameWorld::Instance()->CreateGameObject("Player_brush_left");
		auto player_brush_left = gameObject->AddComponent<HopEngine::BoneComponent>();
		renderer = gameObject->AddComponent<HopEngine::SpriteRendererComponent>();
		renderer->SetTexture(*HopEngine::ResourceSystem::Instance()->GetTextureCopy("player_brush_left_back"));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f - 1, 2);
		renderer->SetPixelSize(renderer->GetSprite()->getTexture()->getSize().x * player_scale, renderer->GetSprite()->getTexture()->getSize().y * player_scale);
		HopEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<HopEngine::LayerRenderingComponent>()->AddToLayer(1, renderer);
		gameObject->AddComponent<HopEngine::RigidbodyComponent>();
		colliders.push_back(gameObject->AddComponent<HopEngine::SpriteColliderComponent>());

		//right
		gameObject = HopEngine::GameWorld::Instance()->CreateGameObject("Player_shoulder_right");
		auto player_shoulder_right = gameObject->AddComponent<HopEngine::BoneComponent>();
		renderer = gameObject->AddComponent<HopEngine::SpriteRendererComponent>();
		renderer->SetTexture(*HopEngine::ResourceSystem::Instance()->GetTextureCopy("player_shoulder_right_front"));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f, 5.f);
		renderer->SetPixelSize(renderer->GetSprite()->getTexture()->getSize().x * player_scale, renderer->GetSprite()->getTexture()->getSize().y * player_scale);
		HopEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<HopEngine::LayerRenderingComponent>()->AddToLayer(3, renderer);
		gameObject->AddComponent<HopEngine::RigidbodyComponent>();
		colliders.push_back(gameObject->AddComponent<HopEngine::SpriteColliderComponent>());

		gameObject = HopEngine::GameWorld::Instance()->CreateGameObject("Player_forearm_right");
		auto player_forearm_right = gameObject->AddComponent<HopEngine::BoneComponent>();
		renderer = gameObject->AddComponent<HopEngine::SpriteRendererComponent>();
		renderer->SetTexture(*HopEngine::ResourceSystem::Instance()->GetTextureCopy("player_forearm_right_front"));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f+1, 4);
		renderer->SetPixelSize(renderer->GetSprite()->getTexture()->getSize().x * player_scale, renderer->GetSprite()->getTexture()->getSize().y * player_scale);
		HopEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<HopEngine::LayerRenderingComponent>()->AddToLayer(3, renderer);
		gameObject->AddComponent<HopEngine::RigidbodyComponent>();
		colliders.push_back(gameObject->AddComponent<HopEngine::SpriteColliderComponent>());

		gameObject = HopEngine::GameWorld::Instance()->CreateGameObject("Player_brush_right");
		auto player_brush_right = gameObject->AddComponent<HopEngine::BoneComponent>();
		renderer = gameObject->AddComponent<HopEngine::SpriteRendererComponent>();
		renderer->SetTexture(*HopEngine::ResourceSystem::Instance()->GetTextureCopy("player_brush_right_front"));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f - 1, 2);
		renderer->SetPixelSize(renderer->GetSprite()->getTexture()->getSize().x * player_scale, renderer->GetSprite()->getTexture()->getSize().y * player_scale);
		HopEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<HopEngine::LayerRenderingComponent>()->AddToLayer(3, renderer);
		gameObject->AddComponent<HopEngine::RigidbodyComponent>();
		colliders.push_back(gameObject->AddComponent<HopEngine::SpriteColliderComponent>());

		//Body
		gameObject = HopEngine::GameWorld::Instance()->CreateGameObject("Player_body");
		auto body = gameObject->AddComponent<HopEngine::BoneComponent>();
		renderer = gameObject->AddComponent<HopEngine::SpriteRendererComponent>();
		renderer->SetTexture(*HopEngine::ResourceSystem::Instance()->GetTextureCopy("player_body"));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f, 0);
		renderer->SetPixelSize(renderer->GetSprite()->getTexture()->getSize().x * player_scale, renderer->GetSprite()->getTexture()->getSize().y * player_scale);
		HopEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<HopEngine::LayerRenderingComponent>()->AddToLayer(2, renderer);
		gameObject->AddComponent<HopEngine::RigidbodyComponent>();
		colliders.push_back(gameObject->AddComponent<HopEngine::SpriteColliderComponent>());

		//Create skeleton

		body->AddChild({ head, std::default_delete<HopEngine::BoneComponent>() }, -1*player_scale, 0.f);
		
		//left arm
		body->AddChild({ player_shoulder_left, std::default_delete<HopEngine::BoneComponent>()}, 20.f * player_scale,
			(body->GetGameObject()->GetComponent < HopEngine::SpriteRendererComponent>()->GetSprite()->getTexture()->getSize().x / 2.f + 2) * player_scale );
		player_shoulder_left->AddChild({ player_forearm_left, std::default_delete<HopEngine::BoneComponent>() }, 
			(player_shoulder_left->GetGameObject()->GetComponent < HopEngine::SpriteRendererComponent>()->GetSprite()->getTexture()->getSize().y - 8) * player_scale, 0);
		player_forearm_left->AddChild({ player_brush_left , std::default_delete<HopEngine::BoneComponent>() }, 
			(player_forearm_left->GetGameObject()->GetComponent < HopEngine::SpriteRendererComponent>()->GetSprite()->getTexture()->getSize().y - 6) * player_scale, 0);

		//right arm
		body->AddChild({ player_shoulder_right, std::default_delete<HopEngine::BoneComponent>() }, 20.f * player_scale,
			-1*(body->GetGameObject()->GetComponent < HopEngine::SpriteRendererComponent>()->GetSprite()->getTexture()->getSize().x / 2.f + 2)* player_scale);
		player_shoulder_right->AddChild({ player_forearm_right, std::default_delete<HopEngine::BoneComponent>() },
			(player_shoulder_right->GetGameObject()->GetComponent < HopEngine::SpriteRendererComponent>()->GetSprite()->getTexture()->getSize().y - 8)* player_scale, 0);
		player_forearm_right->AddChild({ player_brush_right , std::default_delete<HopEngine::BoneComponent>() },
			(player_forearm_right->GetGameObject()->GetComponent < HopEngine::SpriteRendererComponent>()->GetSprite()->getTexture()->getSize().y - 6)* player_scale, 0);

		//left leg
		body->AddChild({ player_hip_left, std::default_delete<HopEngine::BoneComponent>() }, 
			(body->GetGameObject()->GetComponent < HopEngine::SpriteRendererComponent>()->GetSprite()->getTexture()->getSize().y) * player_scale,
			(body->GetGameObject()->GetComponent < HopEngine::SpriteRendererComponent>()->GetSprite()->getTexture()->getSize().x / 2.f - 9) * player_scale);
		player_hip_left->AddChild({ player_shin_left, std::default_delete<HopEngine::BoneComponent>() },
			(player_hip_left->GetGameObject()->GetComponent < HopEngine::SpriteRendererComponent>()->GetSprite()->getTexture()->getSize().y - 8) * player_scale, 0);
		player_shin_left->AddChild({ player_foot_left , std::default_delete<HopEngine::BoneComponent>() },
			(player_shin_left->GetGameObject()->GetComponent < HopEngine::SpriteRendererComponent>()->GetSprite()->getTexture()->getSize().y - 4.f) * player_scale, -4*player_scale);

		//right leg
		body->AddChild({ player_hip_right, std::default_delete<HopEngine::BoneComponent>() },
			(body->GetGameObject()->GetComponent < HopEngine::SpriteRendererComponent>()->GetSprite()->getTexture()->getSize().y)* player_scale,
			-1*(body->GetGameObject()->GetComponent < HopEngine::SpriteRendererComponent>()->GetSprite()->getTexture()->getSize().x / 2.f - 11)* player_scale);
		player_hip_right->AddChild({ player_shin_right, std::default_delete<HopEngine::BoneComponent>() },
			(player_hip_right->GetGameObject()->GetComponent < HopEngine::SpriteRendererComponent>()->GetSprite()->getTexture()->getSize().y - 8)* player_scale, 0);
		player_shin_right->AddChild({ player_foot_right , std::default_delete<HopEngine::BoneComponent>() },
			(player_shin_right->GetGameObject()->GetComponent < HopEngine::SpriteRendererComponent>()->GetSprite()->getTexture()->getSize().y - 4.f)* player_scale, -4 * player_scale);
		
		for (int i = 0; i < colliders.size(); ++i) {
			for (int j = 0; j < colliders.size(); ++j) {
				if (i == j) continue;
				colliders[i]->AddIgnoreCollision(colliders[j]);
			}
		}

		player_hip_right->GetGameObject()->GetComponent<HopEngine::TransformComponent>()->SetLocalRotation(-60);
		player_shin_right->GetGameObject()->GetComponent<HopEngine::TransformComponent>()->SetLocalRotation(-60);
		player_shoulder_left->GetGameObject()->GetComponent<HopEngine::TransformComponent>()->SetLocalRotation(90);

	}

	HopEngine::GameObject* Player::GetGameObject()
	{
		return gameObject;
	}
}