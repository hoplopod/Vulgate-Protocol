#pragma once

#include "SpineComponent.h"
#include "InputComponent.h"
#include "TimerSystem.h"
#include "PVEComponent.h"

namespace HopEngine {

	enum class PlayerState {other, attack, block, stan, other_attack};

	enum class PlayerDirection {left, right};

	enum class BladeState {Close, Open};

	class PlayerSpineComponent : public SpineComponent {
	public:
		PlayerSpineComponent(GameObject* gameObject);

		void Update(float deltaTime) override;

		void callback(spine::AnimationState* state, spine::EventType type, spine::TrackEntry* entry, spine::Event* event);

		PlayerState checkPlayerState() const;
		PlayerDirection checkPlayerDir() const;
		BladeState checkBladeState() const;
		
	private:
		spine::String skin = "standart_right_direction";

		PlayerState state = PlayerState::other;
		PlayerDirection dir = PlayerDirection::right;
		BladeState bladeState = BladeState::Open;

		InputComponent* input;
		PVEComponent* pve;

		bool stanConsumed = false;
	};

}