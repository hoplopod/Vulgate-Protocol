#pragma once

#include "SpineComponent.h"
#include "InputComponent.h"

namespace HopEngine {

	enum class PlayerDirection {left, right};

	enum class BladeState {Close, Open};

	class PlayerSpineComponent : public SpineComponent {
	public:
		PlayerSpineComponent(GameObject* gameObject);

		void Update(float deltaTime) override;

		void callback(spine::AnimationState* state, spine::EventType type, spine::TrackEntry* entry, spine::Event* event);
		
	private:
		spine::String skin = "standart_left_direction";

		PlayerDirection dir = PlayerDirection::left;
		BladeState bladeState = BladeState::Open;

		InputComponent* input;
	};

}