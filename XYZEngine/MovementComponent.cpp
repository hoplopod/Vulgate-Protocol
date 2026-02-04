#include "pch.h"
#include "MovementComponent.h"
#include "ColliderComponent.h"

HopEngine::MovementComponent::MovementComponent(GameObject* gameObject)
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

void HopEngine::MovementComponent::Update(float deltaTime)
{
	horizontalAxis = 0.f;

	switch (input->GetPlayerMoveState())
	{
		case CharacterMoveState::Stand: {
			break;
		}
		case CharacterMoveState::Walk_Left: {
			horizontalAxis -= 1.f;
			break;
		}
		case CharacterMoveState::Walk_Right: {
			horizontalAxis += 1.f;
			break;
		}
	default:
		break;
	}

	if (gameObject->GetComponent<ColliderComponent>() != nullptr) {
		auto collision = gameObject->GetComponent<ColliderComponent>();

		if (collision->GetCollision()[0] == -1 * horizontalAxis)  horizontalAxis = 0;

		if (collision->GetCollision()[1] == -1)  status = ObjectStatus::stable;
	}
	

	switch (status)
	{
	case HopEngine::ObjectStatus::stable:
		verticalAxis = 0.f;
		break;
	case HopEngine::ObjectStatus::shattered:
		verticalAxis = -9.8f;
		break;
	default:
		break;
	}

	transform->MoveBy(deltaTime * Vector2Df{ speed * horizontalAxis, weight * verticalAxis });

	acceleration = transform->GetWorldPosition() - previousPosition;
	previousPosition = transform->GetWorldPosition();
}

void HopEngine::MovementComponent::Render()
{
}

float HopEngine::MovementComponent::GetHorizontalAxis() const{
	return horizontalAxis;
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

void HopEngine::MovementComponent::SetWeight(float newWeight)
{
	weight = newWeight;
}

void HopEngine::MovementComponent::SetStableAngle(Vector2Df newStableAngle)
{
	stableAngle = newStableAngle;
}
