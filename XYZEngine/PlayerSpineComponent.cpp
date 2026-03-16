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

	//move
	float xAxis = input->GetHorizontalAxis();
	if (xAxis != 0) {
		if (xAxis > 0) {
			dir = PlayerDirection::left;
			if(skeletonTransform->getSkin()->getName() == "standart_right_direction") skeletonTransform->setSkin("standart_left_direction");
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
	} else this->TryToSetAnimation_num(1);

	//switch blade
	bool switched = input->GetSwitchedBlade();
	if (switched) {
		int num = 3;
		switch (dir)
		{
		case HopEngine::PlayerDirection::left: num = 4; break;
		case HopEngine::PlayerDirection::right: num = 5; break;
		}
		drawable->state->setAnimation(animations->at(num).second.first, animations->at(num).first, animations->at(num).second.second);
	}
}

void HopEngine::PlayerSpineComponent::callback(spine::AnimationState* state, spine::EventType type, spine::TrackEntry* entry, spine::Event* event)
{
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
