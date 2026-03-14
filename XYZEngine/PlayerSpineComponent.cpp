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
			if(skeletonTransform->getSkin()->getName() == "standart_right_direction") skeletonTransform->setSkin("standart_left_direction");
			skeletonTransform->setScaleX(1);
		}
		else {
			if (skeletonTransform->getSkin()->getName() == "standart_left_direction") skeletonTransform->setSkin("standart_right_direction");
			skeletonTransform->setScaleX(-1);
		}
		this->TryToSetAnimation_num(2);
	} else this->TryToSetAnimation_num(1);
}

void HopEngine::PlayerSpineComponent::callback(spine::AnimationState* state, spine::EventType type, spine::TrackEntry* entry, spine::Event* event)
{

}
