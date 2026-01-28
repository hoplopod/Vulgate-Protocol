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
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f - 2, renderer->GetSprite()->getTexture()->getSize().y - 7);
		renderer->SetPixelSize(renderer->GetSprite()->getTexture()->getSize().x * player_scale, renderer->GetSprite()->getTexture()->getSize().y * player_scale);
		XYZEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<XYZEngine::LayerRenderingComponent>()->AddToLayer(3, renderer);

		//Body
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Player_body");
		auto body = gameObject->AddComponent<XYZEngine::BoneComponent>();
		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
		transform->SetWorldPosition(800,800);

		renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureCopy("player_body"));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f, 0);
		renderer->SetPixelSize(renderer->GetSprite()->getTexture()->getSize().x * player_scale, renderer->GetSprite()->getTexture()->getSize().y * player_scale);
		XYZEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<XYZEngine::LayerRenderingComponent>()->AddToLayer(2, renderer);

		//Arms
		//left
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Player_shoulder_left");
		auto player_shoulder_left = gameObject->AddComponent<XYZEngine::BoneComponent>();

		renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureCopy("player_shoulder_left_back"));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f, 5.f);
		renderer->SetPixelSize(renderer->GetSprite()->getTexture()->getSize().x * player_scale, renderer->GetSprite()->getTexture()->getSize().y * player_scale);
		XYZEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<XYZEngine::LayerRenderingComponent>()->AddToLayer(1, renderer);

		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Player_forearm_left");
		auto player_forearm_left = gameObject->AddComponent<XYZEngine::BoneComponent>();

		renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureCopy("player_forearm_left_back"));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f+1,4);
		renderer->SetPixelSize(renderer->GetSprite()->getTexture()->getSize().x * player_scale, renderer->GetSprite()->getTexture()->getSize().y * player_scale);
		XYZEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<XYZEngine::LayerRenderingComponent>()->AddToLayer(1, renderer);

		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Player_brush_left");
		auto player_brush_left = gameObject->AddComponent<XYZEngine::BoneComponent>();

		renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureCopy("player_brush_left_back"));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f - 1, 2);
		renderer->SetPixelSize(renderer->GetSprite()->getTexture()->getSize().x * player_scale, renderer->GetSprite()->getTexture()->getSize().y * player_scale);
		XYZEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<XYZEngine::LayerRenderingComponent>()->AddToLayer(1, renderer);

		//right
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Player_shoulder_right");
		auto player_shoulder_right = gameObject->AddComponent<XYZEngine::BoneComponent>();

		renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureCopy("player_shoulder_right_front"));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f, 5.f);
		renderer->SetPixelSize(renderer->GetSprite()->getTexture()->getSize().x * player_scale, renderer->GetSprite()->getTexture()->getSize().y * player_scale);
		XYZEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<XYZEngine::LayerRenderingComponent>()->AddToLayer(3, renderer);

		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Player_forearm_right");
		auto player_forearm_right = gameObject->AddComponent<XYZEngine::BoneComponent>();

		renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureCopy("player_forearm_right_front"));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f+1, 4);
		renderer->SetPixelSize(renderer->GetSprite()->getTexture()->getSize().x * player_scale, renderer->GetSprite()->getTexture()->getSize().y * player_scale);
		XYZEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<XYZEngine::LayerRenderingComponent>()->AddToLayer(3, renderer);

		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Player_brush_right");
		auto player_brush_right = gameObject->AddComponent<XYZEngine::BoneComponent>();

		renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureCopy("player_brush_right_front"));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f - 1, 2);
		renderer->SetPixelSize(renderer->GetSprite()->getTexture()->getSize().x * player_scale, renderer->GetSprite()->getTexture()->getSize().y * player_scale);
		XYZEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<XYZEngine::LayerRenderingComponent>()->AddToLayer(3, renderer);

		//Legs
		//left
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Player_hip_left");
		auto player_hip_left = gameObject->AddComponent<XYZEngine::BoneComponent>();

		renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureCopy("player_hip_back"));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f + 1, 5.f);
		renderer->SetPixelSize(renderer->GetSprite()->getTexture()->getSize().x * player_scale, renderer->GetSprite()->getTexture()->getSize().y * player_scale);
		XYZEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<XYZEngine::LayerRenderingComponent>()->AddToLayer(1, renderer);

		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Player_shin_left");
		auto player_shin_left = gameObject->AddComponent<XYZEngine::BoneComponent>();

		renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureCopy("player_shin_back"));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f + 3, 4);
		renderer->SetPixelSize(renderer->GetSprite()->getTexture()->getSize().x * player_scale, renderer->GetSprite()->getTexture()->getSize().y * player_scale);
		XYZEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<XYZEngine::LayerRenderingComponent>()->AddToLayer(1, renderer);

		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Player_foot_left");
		auto player_foot_left = gameObject->AddComponent<XYZEngine::BoneComponent>();

		renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureCopy("player_foot_back"));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f - 4, 2);
		renderer->SetPixelSize(renderer->GetSprite()->getTexture()->getSize().x * player_scale, renderer->GetSprite()->getTexture()->getSize().y * player_scale);
		XYZEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<XYZEngine::LayerRenderingComponent>()->AddToLayer(1, renderer);

		//right
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Player_hip_right");
		auto player_hip_right = gameObject->AddComponent<XYZEngine::BoneComponent>();

		renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureCopy("player_hip_front"));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f + 1, 5.f);
		renderer->SetPixelSize(renderer->GetSprite()->getTexture()->getSize().x* player_scale, renderer->GetSprite()->getTexture()->getSize().y* player_scale);
		XYZEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<XYZEngine::LayerRenderingComponent>()->AddToLayer(2, renderer);

		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Player_shin_right");
		auto player_shin_right = gameObject->AddComponent<XYZEngine::BoneComponent>();

		renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureCopy("player_shin_front"));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f + 3, 4);
		renderer->SetPixelSize(renderer->GetSprite()->getTexture()->getSize().x* player_scale, renderer->GetSprite()->getTexture()->getSize().y* player_scale);
		XYZEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<XYZEngine::LayerRenderingComponent>()->AddToLayer(2, renderer);

		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Player_foot_right");
		auto player_foot_right = gameObject->AddComponent<XYZEngine::BoneComponent>();

		renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureCopy("player_foot_front"));
		renderer->SetOrigin(renderer->GetSprite()->getTexture()->getSize().x / 2.f - 4, 2);
		renderer->SetPixelSize(renderer->GetSprite()->getTexture()->getSize().x* player_scale, renderer->GetSprite()->getTexture()->getSize().y* player_scale);
		XYZEngine::GameWorld::Instance()->FindGameObject("layers_system")->GetComponent<XYZEngine::LayerRenderingComponent>()->AddToLayer(2, renderer);

		//Create skeleton

		body->AddChild({ head, std::default_delete<XYZEngine::BoneComponent>() }, -1*player_scale, 0.f);
		
		//left arm
		body->AddChild({ player_shoulder_left, std::default_delete<XYZEngine::BoneComponent>()}, 20.f * player_scale,
			(body->GetGameObject()->GetComponent < XYZEngine::SpriteRendererComponent>()->GetSprite()->getTexture()->getSize().x / 2.f + 2) * player_scale );
		player_shoulder_left->AddChild({ player_forearm_left, std::default_delete<XYZEngine::BoneComponent>() }, 
			(player_shoulder_left->GetGameObject()->GetComponent < XYZEngine::SpriteRendererComponent>()->GetSprite()->getTexture()->getSize().y - 8) * player_scale, 0);
		player_forearm_left->AddChild({ player_brush_left , std::default_delete<XYZEngine::BoneComponent>() }, 
			(player_forearm_left->GetGameObject()->GetComponent < XYZEngine::SpriteRendererComponent>()->GetSprite()->getTexture()->getSize().y - 6) * player_scale, 0);

		//right arm
		body->AddChild({ player_shoulder_right, std::default_delete<XYZEngine::BoneComponent>() }, 20.f * player_scale,
			-1*(body->GetGameObject()->GetComponent < XYZEngine::SpriteRendererComponent>()->GetSprite()->getTexture()->getSize().x / 2.f + 2)* player_scale);
		player_shoulder_right->AddChild({ player_forearm_right, std::default_delete<XYZEngine::BoneComponent>() },
			(player_shoulder_right->GetGameObject()->GetComponent < XYZEngine::SpriteRendererComponent>()->GetSprite()->getTexture()->getSize().y - 8)* player_scale, 0);
		player_forearm_right->AddChild({ player_brush_right , std::default_delete<XYZEngine::BoneComponent>() },
			(player_forearm_right->GetGameObject()->GetComponent < XYZEngine::SpriteRendererComponent>()->GetSprite()->getTexture()->getSize().y - 6)* player_scale, 0);

		//left leg
		body->AddChild({ player_hip_left, std::default_delete<XYZEngine::BoneComponent>() }, 
			(body->GetGameObject()->GetComponent < XYZEngine::SpriteRendererComponent>()->GetSprite()->getTexture()->getSize().y) * player_scale,
			(body->GetGameObject()->GetComponent < XYZEngine::SpriteRendererComponent>()->GetSprite()->getTexture()->getSize().x / 2.f - 9) * player_scale);
		player_hip_left->AddChild({ player_shin_left, std::default_delete<XYZEngine::BoneComponent>() },
			(player_hip_left->GetGameObject()->GetComponent < XYZEngine::SpriteRendererComponent>()->GetSprite()->getTexture()->getSize().y - 8) * player_scale, 0);
		player_shin_left->AddChild({ player_foot_left , std::default_delete<XYZEngine::BoneComponent>() },
			(player_shin_left->GetGameObject()->GetComponent < XYZEngine::SpriteRendererComponent>()->GetSprite()->getTexture()->getSize().y - 4.f) * player_scale, -4*player_scale);

		//right leg
		body->AddChild({ player_hip_right, std::default_delete<XYZEngine::BoneComponent>() },
			(body->GetGameObject()->GetComponent < XYZEngine::SpriteRendererComponent>()->GetSprite()->getTexture()->getSize().y)* player_scale,
			-1*(body->GetGameObject()->GetComponent < XYZEngine::SpriteRendererComponent>()->GetSprite()->getTexture()->getSize().x / 2.f - 11)* player_scale);
		player_hip_right->AddChild({ player_shin_right, std::default_delete<XYZEngine::BoneComponent>() },
			(player_hip_right->GetGameObject()->GetComponent < XYZEngine::SpriteRendererComponent>()->GetSprite()->getTexture()->getSize().y - 8)* player_scale, 0);
		player_shin_right->AddChild({ player_foot_right , std::default_delete<XYZEngine::BoneComponent>() },
			(player_shin_right->GetGameObject()->GetComponent < XYZEngine::SpriteRendererComponent>()->GetSprite()->getTexture()->getSize().y - 4.f)* player_scale, -4 * player_scale);
		
	}

	XYZEngine::GameObject* Player::GetGameObject()
	{
		return gameObject;
	}
}