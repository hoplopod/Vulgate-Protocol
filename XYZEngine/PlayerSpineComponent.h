#pragma once

#include "SpineComponent.h"
#include "InputComponent.h"

namespace HopEngine {

	enum class PlayerDirection
	{
		left = 0,
		right
	};

	class PlayerSpineComponent : public SpineComponent {
	public:
		PlayerSpineComponent(GameObject* gameObject);

		void Update(float deltaTime) override;

		void callback(spine::AnimationState* state, spine::EventType type, spine::TrackEntry* entry, spine::Event* event);
		
	private:
		spine::String skin = "standart_left_direction";
		PlayerDirection dir = PlayerDirection::left;

		InputComponent* input;
	};

}