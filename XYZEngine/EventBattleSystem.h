#pragma once
#include "PlayerSpineComponent.h"
#include "BaptistSpineComponent.h"

namespace HopEngine {

	class EventBattleSystem {
	public:
		static EventBattleSystem* Instance();

		void TriggerEvent(GameObject* gameObject_1, std::string hitbox_name_1, GameObject* gameObject_2, std::string hitbox_name_2 );

	private:
		EventBattleSystem() {}
		~EventBattleSystem() {}

		EventBattleSystem(EventBattleSystem const&) = delete;
		EventBattleSystem& operator= (EventBattleSystem const&) = delete;
	};

}