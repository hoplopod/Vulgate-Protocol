#pragma once

#include "SpineComponent.h"

namespace HopEngine {

	class PlayerSpineComponent : public SpineComponent {
	public:
		PlayerSpineComponent(GameObject* gameObject);

		void Update(float deltaTime) override;

		void callback(spine::AnimationState* state, spine::EventType type, spine::TrackEntry* entry, spine::Event* event);
		
	private:
		spine::String skin = "";
	};

}