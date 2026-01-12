#include "pch.h"
#include "MovementComponent.h"
#include "ColliderComponent.h"

XYZEngine::MovementComponent::MovementComponent(GameObject* gameObject)
	: Component(gameObject)
{
	input = gameObject->GetComponent<InputComponent>();
	transform = gameObject->GetComponent<TransformComponent>();

	if (input == nullptr)
	{
		std::cout << "Need input component for movement" << std::endl;
		gameObject->RemoveComponent(this);
	}
}

void XYZEngine::MovementComponent::Update(float deltaTime)
{
	float xAxis = input->GetHorizontalAxis();
	float yAxis = input->GetVerticalAxis();

	auto collision = gameObject->GetComponent<ColliderComponent>();
		
	if (collision->GetCollision()[0] == -1*xAxis) xAxis = 0;
	if (collision->GetCollision()[1] == -1*yAxis) yAxis = 0;

	transform->MoveBy(speed * deltaTime * Vector2Df{ xAxis, yAxis });

	acceleration = transform->GetWorldPosition() - previousPosition;
	previousPosition = transform->GetWorldPosition();
}

void XYZEngine::MovementComponent::Render()
{
}

void XYZEngine::MovementComponent::SetSpeed(float newSpeed)
{
	speed = newSpeed;
}

float XYZEngine::MovementComponent::GetSpeed() const
{
	return speed;
}

float XYZEngine::MovementComponent::GetAccelerationSquared() const
{
	return acceleration.x * acceleration.x + acceleration.y * acceleration.y;
}
