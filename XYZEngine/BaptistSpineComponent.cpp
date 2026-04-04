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

	//move
	float xAxis = ai->GetHorizontalAxis();
	if (xAxis != 0) {
		if (xAxis < 0) {
			dir = BaptistDirection::left;
			if (skeletonTransform->getSkin()->getName() == "standart_right_direction") skeletonTransform->setSkin("standart_left_direction");
			skeletonTransform->setScaleX(-1);
		}
		else {
			dir = BaptistDirection::right;
			if (skeletonTransform->getSkin()->getName() == "standart_left_direction") skeletonTransform->setSkin("standart_right_direction");
			skeletonTransform->setScaleX(1);
		}
		this->TryToSetAnimation_num(4);
	}
	else {
		switch (dir)
		{
		case HopEngine::BaptistDirection::left: num = 1; break;
		case HopEngine::BaptistDirection::right: num = 2; break;
		}
		this->TryToSetAnimation_num(num);
	}
}

void HopEngine::BaptistSpineComponent::callback(spine::AnimationState* state, spine::EventType type, spine::TrackEntry* entry, spine::Event* event) {

}
