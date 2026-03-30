#pragma once
#include "BattlesComponent.h"
#include "InputComponent.h"

namespace HopEngine {

	class PlayerBattleComponent : public BattlesComponent {
	public:
		PlayerBattleComponent(GameObject* gameObject);
		~PlayerBattleComponent();

		void Update(float deltaTime) override;
		void Render() override;

		void TriggerEvent(BattlesComponent* component);

	private:
		InputComponent* input;
	};

}