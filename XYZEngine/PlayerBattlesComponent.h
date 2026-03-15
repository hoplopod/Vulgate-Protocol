#pragma once
#include "BattlesComponent.h"

namespace HopEngine {

	class PlayerBattlesComponent : public BattlesComponent {
	public:
		PlayerBattlesComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;
	};

}
