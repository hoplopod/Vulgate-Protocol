#pragma once

#include "TransformComponent.h"
#include "spine/spine-sfml.h"

namespace HopEngine {

	class SpineComponent : public Component, public spine::AnimationStateListenerObject {
	public:
		SpineComponent(GameObject* gameObject);
		~SpineComponent() = default;

		void Update(float deltaTime) {};
		void Render() override;
		void callback(spine::AnimationState* state, spine::EventType type, spine::TrackEntry* entry, spine::Event* event) override;

		virtual void TryToSetAnimation_name(spine::String);
		virtual void TryToSetAnimation_num(int num);

		void SetData(spine::SkeletonData* data);

		void AddAnimations(std::map<int, std::pair < spine::String, std::pair<int, bool >> >* new_animations);

		const spine::Skeleton* getSkeletonTransform();

	protected:
		TransformComponent* transform;
		std::map<int, std::pair<spine::String, std::pair<int, bool>>>* animations;

		spine::SkeletonDrawable* drawable;
		spine::AnimationStateData* stateData;
		spine::Skeleton* skeletonTransform;
		spine::TrackEntry* currentEntry;

	};

}