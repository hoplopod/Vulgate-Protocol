#include "Player.h"
#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>
#include <MovementComponent.h>
#include <SpriteDirectionComponent.h>
#include <SpriteMovementAnimationComponent.h>
#include <LayerRenderingComponent.h>
#include <SpineTriggersSystem.h>

namespace Roguelike
{
	Player::Player(const HopEngine::Vector2Df& position)
	{

		gameObject = HopEngine::GameWorld::Instance()->CreateGameObject("player");
		auto transform = gameObject->GetComponent<HopEngine::TransformComponent>();
		transform->SetWorldPosition(position);

		auto renderer = gameObject->AddComponent<HopEngine::SpriteRendererComponent>();

		auto rigidbody = gameObject->AddComponent<HopEngine::RigidbodyComponent>();

		auto collider = gameObject->AddComponent<HopEngine::SpriteColliderComponent>();
		collider->AddToMapCollision();
		collider->SetMapCollision({ -80, 0, 160, 10 });
		HopEngine::TriggerSystem::Instance()->Subscribe_Camera_HitBox(collider);
		
		auto input = gameObject->AddComponent<HopEngine::InputComponent>();

		auto pve = gameObject->AddComponent<HopEngine::PVEComponent>();
		pve->setMaxHP(20);
		pve->setHP(17);

		pve->onDeath = [this](HopEngine::PVEComponent*)
			{
				HopEngine::GameWorld::Instance()->RequestGameOver();
			};
		pve->onTakeDamageSound = [this]()
			{
				HopEngine::SoundSystem::Instance()->Play_Sound("Sound: enemy hit");
			};

		auto spine = gameObject->AddComponent<HopEngine::PlayerSpineComponent>();
		spine->SetData(HopEngine::ResourceSystem::Instance()->GetSkeletonData("player"));
		spine->setStartSkin("standart_right_direction");

		auto anim = new std::map<int, std::pair<spine::String, std::pair<int, bool>>>(std::move(createAnimations())); 
		spine->AddAnimations(anim);

		HopEngine::SpineTriggerSystem::Instance()->Subscribe_HitBoxes(gameObject, spine, "blade_hitbox_2", "blade_hitbox_2");
		HopEngine::SpineTriggerSystem::Instance()->Subscribe_HitBoxes(gameObject, spine, "blade_hitbox_1", "blade_hitbox_1");
		HopEngine::SpineTriggerSystem::Instance()->Subscribe_HitBoxes(gameObject, spine, "body hitbox", "body hitbox");

		auto movement = gameObject->AddComponent<HopEngine::MovementComponent>();
		movement->SetSpeed(400.f);

		auto ui = gameObject->AddComponent<HopEngine::HealthBarComponent>();
		ui->getBar().setSize({ 200, 10 });
	}

	HopEngine::GameObject* Player::GetGameObject()
	{
		return gameObject;
	}

	std::map<int, std::pair<spine::String, std::pair<int, bool>>> Player::createAnimations()
	{
		std::map<int, std::pair<spine::String, std::pair<int, bool>>> animatioms;

		animatioms.emplace(-2, std::make_pair(spine::String("plug (blade down)"), std::make_pair(2, false)));
		animatioms.emplace(-1, std::make_pair(spine::String("plug (blade up)"), std::make_pair(2, false)));

		animatioms.emplace(1, std::make_pair(spine::String("Stable"), std::make_pair(2, true))); 
		animatioms.emplace(2, std::make_pair(spine::String("Walk forward"), std::make_pair(2, true))); 

		animatioms.emplace(4, std::make_pair(spine::String("blade switch left"), std::make_pair(1, false))); 
		animatioms.emplace(5, std::make_pair(spine::String("blade switch right"), std::make_pair(1, false))); 

		animatioms.emplace(6, std::make_pair(spine::String("Kick down left"), std::make_pair(2, false))); 
		animatioms.emplace(7, std::make_pair(spine::String("Kick down right"), std::make_pair(2, false))); 
		animatioms.emplace(8, std::make_pair(spine::String("Kick top left"), std::make_pair(2, false))); 
		animatioms.emplace(9, std::make_pair(spine::String("Kick top right"), std::make_pair(2, false))); 
		animatioms.emplace(10, std::make_pair(spine::String("Kick in the center left"), std::make_pair(2, false)));
		animatioms.emplace(11, std::make_pair(spine::String("Kick in the center right"), std::make_pair(2, false)));

		animatioms.emplace(12, std::make_pair(spine::String("Stunned"), std::make_pair(2, false)));
		animatioms.emplace(13, std::make_pair(spine::String("Take damage"), std::make_pair(2, false)));

		animatioms.emplace(14, std::make_pair(spine::String("Block left"), std::make_pair(2, false)));
		animatioms.emplace(15, std::make_pair(spine::String("Block right"), std::make_pair(2, false)));

		return animatioms;
	}
}
