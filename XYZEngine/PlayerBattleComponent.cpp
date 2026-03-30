#include "pch.h"
#include "PlayerBattleComponent.h"

HopEngine::PlayerBattleComponent::PlayerBattleComponent(GameObject* gameObject) : BattlesComponent(gameObject)
{
	input = gameObject->GetComponent<InputComponent>();
}

HopEngine::PlayerBattleComponent::~PlayerBattleComponent()
{
}

void HopEngine::PlayerBattleComponent::Update(float deltaTime)
{
}

void HopEngine::PlayerBattleComponent::Render()
{
}

void HopEngine::PlayerBattleComponent::TriggerEvent(BattlesComponent* component)
{
}
