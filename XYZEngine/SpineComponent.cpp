#include "pch.h"
#include "SpineComponent.h"
#include "RenderSystem.h"

HopEngine::SpineComponent::SpineComponent(GameObject* gameObject) : Component(gameObject) {
	transform = gameObject->GetComponent<TransformComponent>();
}

void HopEngine::SpineComponent::Render()
{
	RenderSystem::Instance()->Render(*drawable);
}

void HopEngine::SpineComponent::TryToSetAnimation_name(spine::String name)
{
	spine::TrackEntry* currentEntry = drawable->state->getCurrent(0);

	if (currentEntry) {
		spine::Animation* currentAnimation = currentEntry->getAnimation();

		if (currentAnimation && currentAnimation->getName() == name) {
			return;
		}
	}

	spine::TrackEntry* newEntry = drawable->state->setAnimation(0, name, true);
	if (newEntry) {
		newEntry->setMixDuration(0.2f);
	}
}

void HopEngine::SpineComponent::TryToSetAnimation_num(int num)
{
	if (animations == nullptr) return;

	spine::TrackEntry* currentEntry = drawable->state->getCurrent(animations->at(num).second.first);

	if (currentEntry) {
		spine::Animation* currentAnimation = currentEntry->getAnimation();

		if (currentAnimation && currentAnimation->getName() == animations->at(num).first) {
			return;
		}
	}

	spine::TrackEntry* newEntry = drawable->state->setAnimation(animations->at(num).second.first, animations->at(num).first, animations->at(num).second.second);
	if (newEntry) {
		newEntry->setMixDuration(0.2f);
	}
}

const spine::Skeleton* HopEngine::SpineComponent::getSkeletonTransform()
{
	return skeletonTransform;
}

void HopEngine::SpineComponent::callback(spine::AnimationState* state, spine::EventType type, spine::TrackEntry* entry, spine::Event* event) {
	SP_UNUSED(state);
	const spine::String& animationName = (entry && entry->getAnimation()) ? entry->getAnimation()->getName() : spine::String("");

	switch (type) {
	case spine::EventType_Start:
		printf("%d start: %s\n", entry->getTrackIndex(), animationName.buffer());
		break;
	case spine::EventType_Interrupt:
		printf("%d interrupt: %s\n", entry->getTrackIndex(), animationName.buffer());
		break;
	case spine::EventType_End:
		printf("%d end: %s\n", entry->getTrackIndex(), animationName.buffer());
		break;
	case spine::EventType_Complete:
		printf("%d complete: %s\n", entry->getTrackIndex(), animationName.buffer());
		break;
	case spine::EventType_Dispose:
		printf("%d dispose: %s\n", entry->getTrackIndex(), animationName.buffer());
		break;
	case spine::EventType_Event:
		printf("%d event: %s, %s: %d, %f, %s %f %f\n", entry->getTrackIndex(), animationName.buffer(), event->getData().getName().buffer(), event->getIntValue(), event->getFloatValue(),
			event->getStringValue().buffer(), event->getVolume(), event->getBalance());
		break;
	}
	fflush(stdout);
}

void HopEngine::SpineComponent::SetData(spine::SkeletonData* data)
{
	stateData = new spine::AnimationStateData(data);
	drawable = new spine::SkeletonDrawable(data, stateData);

	drawable->state->setListener(this);
	skeletonTransform = drawable->skeleton;
	skeletonTransform->setScaleY(-1);

}

void HopEngine::SpineComponent::AddAnimations(std::map<int, std::pair<spine::String, std::pair<int, bool>>>* new_animations)
{
	animations = new_animations;
}
