#include "pch.h"
#include "SpineComponent.h"

HopEngine::SpineComponent::SpineComponent(GameObject* gameObject) : Component(gameObject) {}

void HopEngine::SpineComponent::Update(float deltaTime)
{
}

void HopEngine::SpineComponent::Render()
{
}

void HopEngine::SpineComponent::SetData(spine::SkeletonData* data)
{
	stateData = new spine::AnimationStateData(data);
	drawble = new spine::SkeletonDrawable(data, stateData);
}

