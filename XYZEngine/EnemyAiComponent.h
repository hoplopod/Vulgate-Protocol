#pragma once

#include "TransformComponent.h"
#include "PVEComponent.h"

namespace HopEngine {

	class EnemyAiComponent : public Component {
	public:
		EnemyAiComponent(GameObject* gameObject);
		
		void Update(float deltaTime) override;
		void Render() override;

		void SetPurpose(GameObject* gameObject);

		float GetHorizontalAxis() const;

	private:
		TransformComponent* enemy_transform;
		TransformComponent* purpose_transform;

		float horizontalAxis = 0.f;
	};

}
