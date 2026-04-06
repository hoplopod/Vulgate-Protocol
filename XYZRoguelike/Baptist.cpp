#include "Baptist.h"
#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>
#include <SpineTriggersSystem.h>

namespace Roguelike{

	Baptist::Baptist(const HopEngine::Vector2Df& position)
	{
		gameObject = HopEngine::GameWorld::Instance()->CreateGameObject("baptist");
		auto transform = gameObject->GetComponent<HopEngine::TransformComponent>();
		transform->SetWorldPosition(position);

		auto renderer = gameObject->AddComponent<HopEngine::SpriteRendererComponent>();

		auto rigidbody = gameObject->AddComponent<HopEngine::RigidbodyComponent>();

		auto collider = gameObject->AddComponent<HopEngine::SpriteColliderComponent>();
		collider->AddToMapCollision();
		collider->SetMapCollision({ -80, 0, 160, 10 });

		auto pve = gameObject->AddComponent<HopEngine::PVEComponent>();

		auto ai = gameObject->AddComponent<HopEngine::EnemyAiComponent>();
		ai->SetPurpose(HopEngine::GameWorld::Instance()->FindGameObject("player"));
		ai->SetSpeed(250.f);

		auto spine = gameObject->AddComponent<HopEngine::BaptistSpineComponent>();
		spine->SetData(HopEngine::ResourceSystem::Instance()->GetSkeletonData("baptist"));
		spine->setStartSkin("standart_right_direction");

		auto anim = new std::map<int, std::pair<spine::String, std::pair<int, bool>>>(std::move(createAnimations()));
		spine->AddAnimations(anim);

		HopEngine::SpineTriggerSystem::Instance()->Subscribe_HitBoxes(gameObject, spine, "body hitbox", "body hitbox");
		HopEngine::SpineTriggerSystem::Instance()->Subscribe_HitBoxes(gameObject, spine, "Sword right hitbox", "Sword right hitbox");
		HopEngine::SpineTriggerSystem::Instance()->Subscribe_HitBoxes(gameObject, spine, "Sword left hitbox", "Sword left hitbox");

	}

	HopEngine::GameObject* Baptist::GetGameObject()
	{
		return gameObject;
	}

	std::map<int, std::pair<spine::String, std::pair<int, bool>>> Baptist::createAnimations()
	{
		std::map<int, std::pair<spine::String, std::pair<int, bool>>> animatioms;

		animatioms.emplace(-1, std::make_pair(spine::String("Stable left"), std::make_pair(1, true)));
		animatioms.emplace(-2, std::make_pair(spine::String("Stable right"), std::make_pair(1, true)));

		animatioms.emplace(1, std::make_pair(spine::String("Stable left"), std::make_pair(2, true)));
		animatioms.emplace(2, std::make_pair(spine::String("Stable right"), std::make_pair(2, true)));

		animatioms.emplace(3, std::make_pair(spine::String("Walk back"), std::make_pair(2, true)));
		animatioms.emplace(4, std::make_pair(spine::String("Walk forward"), std::make_pair(2, true)));

		animatioms.emplace(5, std::make_pair(spine::String("Parry left down"), std::make_pair(2, false)));
		animatioms.emplace(6, std::make_pair(spine::String("Parry right down"), std::make_pair(2, false)));

		animatioms.emplace(7, std::make_pair(spine::String("Parry left up"), std::make_pair(2, false)));
		animatioms.emplace(8, std::make_pair(spine::String("Parry right up"), std::make_pair(2, false)));

		animatioms.emplace(9, std::make_pair(spine::String("Shock attack from above left"), std::make_pair(2, false)));
		animatioms.emplace(10, std::make_pair(spine::String("Shock attack from above right"), std::make_pair(2, false)));

		animatioms.emplace(11, std::make_pair(spine::String("Shock attack from below left"), std::make_pair(2, false)));
		animatioms.emplace(12, std::make_pair(spine::String("Shock attack from below right"), std::make_pair(2, false)));

		animatioms.emplace(13, std::make_pair(spine::String("Stabbing attack from above left"), std::make_pair(2, false)));
		animatioms.emplace(14, std::make_pair(spine::String("Stabbing attack from above right"), std::make_pair(2, false)));

		animatioms.emplace(15, std::make_pair(spine::String("Stabbing attack from below left"), std::make_pair(2, false)));
		animatioms.emplace(16, std::make_pair(spine::String("Stabbing attack from below right"), std::make_pair(2, false)));

		animatioms.emplace(17, std::make_pair(spine::String("Stabbing attack in the center left"), std::make_pair(2, false)));
		animatioms.emplace(18, std::make_pair(spine::String("Stabbing attack in the center right"), std::make_pair(2, false)));

		animatioms.emplace(19, std::make_pair(spine::String("Take damage"), std::make_pair(2, false)));

		return animatioms;
	}

}