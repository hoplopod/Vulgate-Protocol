#include "pch.h"
#include "BaptistSpineComponent.h"

HopEngine::BaptistSpineComponent::BaptistSpineComponent(GameObject* gameObject) : SpineComponent(gameObject)
{
	ai = gameObject->GetComponent<EnemyAiComponent>();
}

void HopEngine::BaptistSpineComponent::Update(float deltaTime)
{
	skeletonTransform->setPosition(transform->GetWorldPosition().x, transform->GetWorldPosition().y);
	drawable->update(deltaTime);
	int num = 0;
	float time = 0.f;

	if (TimerSystem::Instance()->checkTimer("enemy_action") != TimerState::In_Process) {
		if (ai->getAttackType() != AttackType::None) {
			switch (dir)
			{
			case BaptistDirection::left:
				switch (ai->getAttackType())
				{
				case AttackType::Thrust_Center: num = 17; break;
				case AttackType::Thrust_Down: num = 15; break;
				case AttackType::Thrust_Up: num = 13; break;
				case AttackType::Swing_Up: num = 9; break;
				case AttackType::Swing_Down: num = 11; break;
				}
				break;
			case BaptistDirection::right:
				switch (ai->getAttackType())
				{
				case AttackType::Thrust_Center: num = 18; break;
				case AttackType::Thrust_Down: num = 16; break;
				case AttackType::Thrust_Up: num = 14; break;
				case AttackType::Swing_Up: num = 10; break;
				case AttackType::Swing_Down: num = 12; break;
				}
				break;
			}
			spine::TrackEntry* newEntry = drawable->state->setAnimation(animations->at(num).second.first, animations->at(num).first, animations->at(num).second.second);
			newEntry->setMixDuration(0.01f);
			newEntry->setTimeScale(0.6f);
			TimerSystem::Instance()->addTimer("enemy_action", 1.f);
			return;
		}

		//move
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

void HopEngine::BaptistSpineComponent::callback(spine::AnimationState* state, spine::EventType type, spine::TrackEntry* entry, spine::Event* event) {

}
