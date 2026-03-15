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

	bool switched = input->GetSwitchedBlade();
	if (switched) {
		this->TryToSetAnimation_num(3);
	}
}

void HopEngine::PlayerSpineComponent::callback(spine::AnimationState* state, spine::EventType type, spine::TrackEntry* entry, spine::Event* event)
{
	//switch blade
	if (entry->getAnimation()->getName() == animations->at(3).first && type == spine::EventType_Start) {
		switch (dir)
		{
		case HopEngine::PlayerDirection::left:
			this->TryToSetAnimation_num(4);
			break;
		case HopEngine::PlayerDirection::right:
			this->TryToSetAnimation_num(5);
			break;
		}
	}
}
