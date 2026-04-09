#pragma once

#include "SpineComponent.h"
#include "TimerSystem.h"
#include "EnemyAiComponent.h"
#include "PVEComponent.h"

namespace HopEngine {

	enum class BaptistState {other, attack, block, stan, damages};

	enum class BaptistDirection { left, right };

	class BaptistSpineComponent : public SpineComponent {
	public:
		BaptistSpineComponent(GameObject* gameObject);

		void Update(float deltaTime) override;

		BaptistDirection checkBaptistDir() const;
		BaptistState checkBaptistState() const;

		void callback(spine::AnimationState* state, spine::EventType type, spine::TrackEntry* entry, spine::Event* event);

	private:
		spine::String skin = "standart_left_direction";

		BaptistDirection dir = BaptistDirection::left;
		BaptistState state = BaptistState::other;

		EnemyAiComponent* ai;
		PVEComponent* pve;

		bool blockConsumed = false;
		bool damageConsumed = false;
		bool stanConsumed = false;
	};

}