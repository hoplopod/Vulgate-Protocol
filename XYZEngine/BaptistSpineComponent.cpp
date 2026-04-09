#include "pch.h"
#include "BaptistSpineComponent.h"

HopEngine::BaptistSpineComponent::BaptistSpineComponent(GameObject* gameObject) : SpineComponent(gameObject)
{
	ai = gameObject->GetComponent<EnemyAiComponent>();
	pve = gameObject->GetComponent<PVEComponent>();
}

void HopEngine::BaptistSpineComponent::Update(float deltaTime)
{
	skeletonTransform->setPosition(transform->GetWorldPosition().x, transform->GetWorldPosition().y);
	drawable->update(deltaTime);
	int num = 0;
	float time = 0.f;

	bool stan = pve->getStanned();
	if (stan && !stanConsumed) {
		stanConsumed = true;
		switch (dir)
		{
		case BaptistDirection::left: num = 21; break;
		case BaptistDirection::right: num = 22; break;
		}
		drawable->state->setAnimation(animations->at(num).second.first, animations->at(num).first, animations->at(num).second.second);
		TimerSystem::Instance()->addTimer("enemy_action", 1.8f);
		state = BaptistState::stan;
		return;
	}
	else if (!stan) stanConsumed = false;

	bool block = pve->getBlocked();
	if (block && !blockConsumed && state != BaptistState::stan) {
		blockConsumed = true;
		switch (dir)
		{
		case HopEngine::BaptistDirection::left: num = 7; break;
		case HopEngine::BaptistDirection::right: num = 8; break;
		}
		spine::TrackEntry* newEntry = drawable->state->setAnimation(animations->at(num).second.first, animations->at(num).first, animations->at(num).second.second);
		TimerSystem::Instance()->addTimer("enemy_action", 1.4f);
		state = BaptistState::block;
		return;
	}
	else if (!block) blockConsumed = false;

	bool damage = pve->getTakedDamage();
	if (damage && !damageConsumed && state == BaptistState::stan) {
		damageConsumed = true;
		switch (dir)
		{
		case BaptistDirection::left: num = 19; break;
		case BaptistDirection::right: num = 20; break;
		}
		drawable->state->setAnimation(animations->at(num).second.first, animations->at(num).first, animations->at(num).second.second);
		TimerSystem::Instance()->addTimer("enemy_action", 2.3f);
		state = BaptistState::damages;
		return;
	}
	else if (!damage) damageConsumed = false;

	if (TimerSystem::Instance()->checkTimer("enemy_action") != TimerState::In_Process && state != BaptistState::stan) {

		if (ai->getAttackType() != AttackType::None && state != BaptistState::attack) {
			switch (dir)
			{
			case BaptistDirection::left:
				switch (ai->getAttackType())
				{
				case AttackType::Thrust_Center: num = 17; time = 0.8f; break;
				case AttackType::Thrust_Down: num = 15; time = 1.0f; break;
				case AttackType::Thrust_Up: num = 13; time = 1.0f; break;
				case AttackType::Swing_Up: num = 9; time = 1.4f; break;
				case AttackType::Swing_Down: num = 11; time = 1.4f; break;
				}
				break;
			case BaptistDirection::right:
				switch (ai->getAttackType())
				{
				case AttackType::Thrust_Center: num = 18; time = 0.8f; break;
				case AttackType::Thrust_Down: num = 16; time = 1.0f; break;
				case AttackType::Thrust_Up: num = 14; time = 1.0f; break;
				case AttackType::Swing_Up: num = 10; time = 1.4f; break;
				case AttackType::Swing_Down: num = 12; time = 1.4f; break;
				}
				break;
			}
			spine::TrackEntry* newEntry = drawable->state->setAnimation(animations->at(num).second.first, animations->at(num).first, animations->at(num).second.second);
			newEntry->setTimeScale(0.5f);
			TimerSystem::Instance()->addTimer("enemy_action", time);
			state = BaptistState::attack;
			return;
		}

		//move
		state = BaptistState::other;
		float xAxis = ai->GetHorizontalAxis();
		auto rot = ai->getDir();
		if (rot == -1) {
			dir = BaptistDirection::left;
			if (skeletonTransform->getSkin()->getName() == "standart_right_direction") skeletonTransform->setSkin("standart_left_direction");
			skeletonTransform->setScaleX(rot);
			this->TryToSetAnimation_num(-1);
		}
		else {
			dir = BaptistDirection::right;
			if (skeletonTransform->getSkin()->getName() == "standart_left_direction") skeletonTransform->setSkin("standart_right_direction");
			skeletonTransform->setScaleX(rot);
			this->TryToSetAnimation_num(-2);
		}

		if (xAxis != 0) {
			if (xAxis < 0) {
				switch (dir)
				{
				case BaptistDirection::left: num = 4; break;
				case BaptistDirection::right: num = 3; break;
				}
			}
			else {
				switch (dir)
				{
				case BaptistDirection::left: num = 3; break;
				case BaptistDirection::right: num = 4; break;
				}
			}
		}
		else {
			switch (dir)
			{
			case BaptistDirection::left: num = 1; break;
			case BaptistDirection::right: num = 2; break;
			}
		}
		this->TryToSetAnimation_num(num);

	}

}

HopEngine::BaptistDirection HopEngine::BaptistSpineComponent::checkBaptistDir() const
{
	return dir;
}

HopEngine::BaptistState HopEngine::BaptistSpineComponent::checkBaptistState() const
{
	return state;
}

void HopEngine::BaptistSpineComponent::callback(spine::AnimationState* state, spine::EventType type, spine::TrackEntry* entry, spine::Event* event) {

}
