#include "pch.h"
#include "EnemyAiComponent.h"

HopEngine::EnemyAiComponent::EnemyAiComponent(GameObject* gameObject) : Component(gameObject)
{
	enemy_transform = gameObject->GetComponent<TransformComponent>();
}

void HopEngine::EnemyAiComponent::Update(float deltaTime)
{
}

void HopEngine::EnemyAiComponent::Render()
{
}

void HopEngine::EnemyAiComponent::SetPurpose(GameObject* gameObject)
{
	purpose_transform = gameObject->GetComponent<TransformComponent>();
}

float HopEngine::EnemyAiComponent::GetHorizontalAxis() const
{
	return horizontalAxis;
}
