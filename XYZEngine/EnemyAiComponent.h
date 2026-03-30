#pragma once

#include "TransformComponent.h"

namespace HopEngine {

	class EnemyAiComponent : public Component {
	public:
		EnemyAiComponent(GameObject* gameObject);
		
		void Update(float deltaTime) override;
		void Render() override;

	};

}
