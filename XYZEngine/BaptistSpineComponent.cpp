#include "pch.h"
#include "BaptistSpineComponent.h"

HopEngine::BaptistSpineComponent::BaptistSpineComponent(GameObject* gameObject) : SpineComponent(gameObject)
{
}

void HopEngine::BaptistSpineComponent::Update(float deltaTime)
{
	skeletonTransform->setPosition(transform->GetWorldPosition().x, transform->GetWorldPosition().y);
	drawable->update(deltaTime);
}

void HopEngine::BaptistSpineComponent::callback(spine::AnimationState* state, spine::EventType type, spine::TrackEntry* entry, spine::Event* event) {

}
