#include "pch.h"
#include "SpineComponent.h"
#include "RenderSystem.h"

HopEngine::SpineComponent::SpineComponent(GameObject* gameObject) : Component(gameObject) {}

void HopEngine::SpineComponent::Update(float deltaTime)
{
	drawable->update(deltaTime);
}

void HopEngine::SpineComponent::Render()
{
	RenderSystem::Instance()->Render(*drawable);
}

void HopEngine::SpineComponent::SetData(spine::SkeletonData* data)
{
	stateData = new spine::AnimationStateData(data);
	drawable = new spine::SkeletonDrawable(data, stateData);
	skeletonTransform = drawable->skeleton;
	skeletonTransform->setPosition(0, 0);
	skeletonTransform->setScaleY(-1);
	if (animation.length() > 0) drawable->state->setAnimation(0, animation, true);
	if (skin.length() > 0) drawable->skeleton->setSkin(skin);
	
}

const spine::Skeleton* HopEngine::SpineComponent::getSkeletonTransform()
{
	return skeletonTransform;
}

