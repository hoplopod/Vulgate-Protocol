#include "pch.h"
#include "BattlesComponent.h"

HopEngine::BattlesComponent::BattlesComponent(GameObject* gameObject) : Component(gameObject)
{
}

void HopEngine::BattlesComponent::Update(float deltaTime) {

}

void HopEngine::BattlesComponent::Render() {

}

void HopEngine::BattlesComponent::setHealthPoints(int newHP)
{
	hp = newHP;
}

void HopEngine::BattlesComponent::takeDamage(int damage)
{
	hp -= damage;
}
