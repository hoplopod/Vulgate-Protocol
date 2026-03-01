#pragma once

#include "TransformComponent.h"
#include "spine/spine-sfml.h"

namespace HopEngine {

	class SpineComponent : public Component {
	public:
		SpineComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void SetData(spine::SkeletonData* data);

		const spine::Skeleton* getSkeletonTransform();

	private:
		TransformComponent* transform;

		spine::SkeletonDrawable* drawable;
		spine::AnimationStateData* stateData;
		spine::Skeleton* skeletonTransform;

		spine::String animation = "Stable";
		spine::String skin = "default";

	};

}