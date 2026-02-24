#pragma once

#include "Component.h"
#include "spine/spine-sfml.h"

namespace HopEngine {

	class SpineComponent : public Component {
	public:
		SpineComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void SetData(spine::SkeletonData* data);

	private:
		spine::SkeletonDrawable* drawble;
		spine::AnimationStateData* stateData;

	};

}