#include "pch.h"
#include "PlayerSpineComponent.h"

HopEngine::PlayerSpineComponent::PlayerSpineComponent(GameObject* gameObject) : SpineComponent(gameObject)
{
}

void HopEngine::PlayerSpineComponent::Update(float deltaTime)
{
	skeletonTransform->setPosition(transform->GetWorldPosition().x, transform->GetWorldPosition().y);
	drawable->update(deltaTime);
}

void HopEngine::PlayerSpineComponent::callback(spine::AnimationState* state, spine::EventType type, spine::TrackEntry* entry, spine::Event* event)
{
}
