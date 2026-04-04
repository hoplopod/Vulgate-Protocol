#pragma once

#include "SpineComponent.h"
#include "TimerSystem.h"
#include "EnemyAiComponent.h"

namespace HopEngine {

	enum class BaptistState {other, attack, block};

	enum class BaptistDirection { left, right };

	enum class AttackType {};

	class BaptistSpineComponent : public SpineComponent {
	public:
		BaptistSpineComponent(GameObject* gameObject);

		void Update(float deltaTime) override;

		void callback(spine::AnimationState* state, spine::EventType type, spine::TrackEntry* entry, spine::Event* event);

	private:
		spine::String skin = "standart_left_direction";

		BaptistDirection dir = BaptistDirection::left;

		EnemyAiComponent* ai;
	};

}