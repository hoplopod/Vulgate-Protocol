#include "pch.h"
#include "SpriteDirectionComponent.h"

HopEngine::SpriteDirectionComponent::SpriteDirectionComponent(GameObject* gameObject)
	: Component(gameObject)
{
	move = gameObject->GetComponent<MovementComponent>();
	spriteRenderer = gameObject->GetComponent<SpriteRendererComponent>();
}

void HopEngine::SpriteDirectionComponent::Update(float deltaTime)
{
	if (move->GetHorizontalAxis() < 0)
	{
		spriteRenderer->FlipX(true);
	}
	if (move->GetHorizontalAxis() > 0)
	{
		spriteRenderer->FlipX(false);
	}
}

void HopEngine::SpriteDirectionComponent::Render()
{
}
