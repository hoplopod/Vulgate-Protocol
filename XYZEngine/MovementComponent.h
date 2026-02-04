#pragma once
#include "GameObject.h"
#include "InputComponent.h"

namespace HopEngine
{
	enum class ObjectStatus {
		stable = 0,
		shattered
	};

	class MovementComponent : public Component
	{
	public:
		MovementComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void SetSpeed(float newSpeed);
		float GetSpeed() const;
		float GetAccelerationSquared() const;

		void SetWeight(float newWeight);
		void SetStableAngle(Vector2Df newStableAngle);

		float GetHorizontalAxis() const;
	private:
		InputComponent* input;
		TransformComponent* transform;

		float speed = 0;
		Vector2Df previousPosition = { 0, 0 };
		Vector2Df acceleration = { 0, 0 };

		float horizontalAxis = 0.f;
		float verticalAxis = 0.f;

		ObjectStatus status = ObjectStatus::shattered;
		float weight = 0;
		Vector2Df stableAngle = { 0,0 };
	};
}