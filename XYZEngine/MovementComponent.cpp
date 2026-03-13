#include "pch.h"
#include "MovementComponent.h"
#include "ColliderComponent.h"

HopEngine::MovementComponent::MovementComponent(GameObject* gameObject)
	: Component(gameObject)
{
	input = gameObject->GetComponent<InputComponent>();
	transform = gameObject->GetComponent<TransformComponent>();
	animation = gameObject->GetComponent<PlayerSpineComponent>();

	if (input == nullptr)
	{
		std::cout << "Need input component for movement" << std::endl;
		gameObject->RemoveComponent(this);
	}
}

void HopEngine::MovementComponent::Update(float deltaTime)
{
	float xAxis = input->GetHorizontalAxis();
	float yAxis = input->GetVerticalAxis();

	if (xAxis != 0) {
		animation->TryToSetAnimation_num(2);
	} else animation->TryToSetAnimation_num(1);

	if (gameObject->GetComponent<ColliderComponent>() != nullptr) {
		auto collision = gameObject->GetComponent<ColliderComponent>();
		if (collision->GetCollision()[0] == -1 * xAxis)  xAxis = 0;
	}

	transform->MoveBy(speed * deltaTime * Vector2Df{ xAxis, yAxis });

	acceleration = transform->GetWorldPosition() - previousPosition;
	previousPosition = transform->GetWorldPosition();
}

void HopEngine::MovementComponent::Render()
{
}

void HopEngine::MovementComponent::SetSpeed(float newSpeed)
{
	speed = newSpeed;
}

float HopEngine::MovementComponent::GetSpeed() const
{
	return speed;
}

float HopEngine::MovementComponent::GetAccelerationSquared() const
{
	return acceleration.x * acceleration.x + acceleration.y * acceleration.y;
}

