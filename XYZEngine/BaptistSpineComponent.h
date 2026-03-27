#pragma once

#include "SpineComponent.h"
#include "TimerSystem.h"

namespace HopEngine {

	enum class BaptistDirection { left, right };

	class BaptistSpineComponent : public SpineComponent {
	public:
		BaptistSpineComponent(GameObject* gameObject);

		void Update(float deltaTime) override;

		void callback(spine::AnimationState* state, spine::EventType type, spine::TrackEntry* entry, spine::Event* event);

	private:
		spine::String skin = "standart_right_direction";

		BaptistDirection dir = BaptistDirection::right;
	};

}