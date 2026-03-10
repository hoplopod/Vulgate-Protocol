#pragma once

#include "TransformComponent.h"
#include "spine/spine-sfml.h"

namespace HopEngine {

	class SpineComponent : public Component, public spine::AnimationStateListenerObject {
	public:
		SpineComponent(GameObject* gameObject);
		~SpineComponent() = default;

		void Update(float deltaTime);
		void Render() override;
		void callback(spine::AnimationState* state, spine::EventType type, spine::TrackEntry* entry, spine::Event* event) override;

		void TryToSetAnimation(std::string name, int trackIndex);

		void SetData(spine::SkeletonData* data);

		const spine::Skeleton* getSkeletonTransform();

	protected:
		TransformComponent* transform;

		spine::SkeletonDrawable* drawable;
		spine::AnimationStateData* stateData;
		spine::Skeleton* skeletonTransform;
		spine::TrackEntry* currentEntry;

	};

}