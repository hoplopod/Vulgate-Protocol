#include "pch.h"
#include "PlayerSpineComponent.h"

HopEngine::PlayerSpineComponent::PlayerSpineComponent(GameObject* gameObject) : SpineComponent(gameObject)
{
	input = gameObject->GetComponent<InputComponent>();
}

void HopEngine::PlayerSpineComponent::Update(float deltaTime)
{
	skeletonTransform->setPosition(transform->GetWorldPosition().x, transform->GetWorldPosition().y);
	drawable->update(deltaTime);

	if (bladeState == BladeState::Open) int num_plug = -1;
	else int num_plug = -2;

	if (TimerSystem::Instance()->checkTimer("player_action") != TimerState::In_Process) {
		int num = 0;

		//player kick
		bool kick = input->GetPlayerKick();
		if (kick) {
			switch (dir)
			{
			case HopEngine::PlayerDirection::left: if (bladeState == BladeState::Close) num = 6; else num = 8; break;
			case HopEngine::PlayerDirection::right: if (bladeState == BladeState::Close) num = 7; else num = 9; break;
			}
			drawable->state->setAnimation(animations->at(num).second.first, animations->at(num).first, animations->at(num).second.second);
			TimerSystem::Instance()->addTimer("player_action", 0.5f);
			return;
		}

		//player block
		bool block = input->GetPlayerBlock();
		if (block) {
			switch (dir)
			{
			case HopEngine::PlayerDirection::left: num = 14; break;
			case HopEngine::PlayerDirection::right: num = 15;  break;
			}
			drawable->state->setAnimation(animations->at(num).second.first, animations->at(num).first, animations->at(num).second.second);
			TimerSystem::Instance()->addTimer("player_action", 0.6f);
			return;
		}

		//player stab
		bool stab = input->GetPlayerStab();
		if (stab) {
			switch (dir)
			{
			case HopEngine::PlayerDirection::left: num = 10; break;
			case HopEngine::PlayerDirection::right: num = 11;  break;
			}
			drawable->state->setAnimation(animations->at(num).second.first, animations->at(num).first, animations->at(num).second.second);
			TimerSystem::Instance()->addTimer("player_action", 0.5f);
			return;
		}

		if (TimerSystem::Instance()->checkTimer("blade_switch") != TimerState::In_Process) {
			//switch blade
			bool switched = input->GetSwitchedBlade();
			if (switched) {
				switch (dir)
				{
				case HopEngine::PlayerDirection::left: num = 4; break;
				case HopEngine::PlayerDirection::right: num = 5; break;
				}
				drawable->state->setAnimation(animations->at(num).second.first, animations->at(num).first, animations->at(num).second.second);
				TimerSystem::Instance()->addTimer("blade_switch", 0.6f);
			}
		}

		//move
		float xAxis = input->GetHorizontalAxis();
		if (xAxis != 0) {
			if (xAxis > 0) {
				dir = PlayerDirection::left;
				if (skeletonTransform->getSkin()->getName() == "standart_right_direction") skeletonTransform->setSkin("standart_left_direction");
				skeletonTransform->setScaleX(1);
				skeletonTransform->setAttachment("Blade2", nullptr);
				skeletonTransform->setAttachment("Blade", "skin");
			}
			else {
				dir = PlayerDirection::right;
				if (skeletonTransform->getSkin()->getName() == "standart_left_direction") skeletonTransform->setSkin("standart_right_direction");
				skeletonTransform->setScaleX(-1);
				skeletonTransform->setAttachment("Blade", nullptr);
				skeletonTransform->setAttachment("Blade2", "skin");
			}
			this->TryToSetAnimation_num(2);
		}
		else this->TryToSetAnimation_num(1);
	}

}

void HopEngine::PlayerSpineComponent::callback(spine::AnimationState* state, spine::EventType type, spine::TrackEntry* entry, spine::Event* event)
{
	entry->setTimeScale(1.0f);

	//switch blade
	if (entry->getAnimation()->getName() == animations->at(4).first || entry->getAnimation()->getName() == animations->at(5).first) {

		if (type == spine::EventType_Start) {
			if (bladeState == BladeState::Open) {
				entry->setTrackTime(0);
				entry->setTimeScale(0.7);
				bladeState = BladeState::Close;
			}
			else if (bladeState == BladeState::Close) {
				entry->setTrackTime(entry->getAnimation()->getDuration());
				entry->setTimeScale(-0.7);
				bladeState = BladeState::Open;
			}
		}
	}

}
