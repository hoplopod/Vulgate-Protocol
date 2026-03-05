#pragma once

#include "TransformComponent.h"
#include "spine/spine-sfml.h"

namespace HopEngine {

	class SpineComponent : public Component {
	public:
		SpineComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void callback(spine::AnimationState* state, spine::EventType type, spine::TrackEntry* entry, spine::Event* event);

		void SetData(spine::SkeletonData* data);

		const spine::Skeleton* getSkeletonTransform();

	private:
		TransformComponent* transform;

		spine::SkeletonDrawable* drawable;
		spine::AnimationStateData* stateData;
		spine::Skeleton* skeletonTransform;

		spine::String animation1 = "Stable";
		spine::String animation2 = "walk (test)";
		spine::String skin = "";

	};

}