#include "pch.h"
#include "InputComponent.h"
#include "Logger.h"

namespace HopEngine
{
	InputComponent::InputComponent(GameObject* gameObject) : Component(gameObject) {}

	void InputComponent::Update(float deltaTime)
	{
		//Move
		playerMoveState = CharacterMoveState::Stand;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			playerMoveState = CharacterMoveState::Walk_Right;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			playerMoveState = CharacterMoveState::Walk_Left;
		}
	}
	void InputComponent::Render()
	{

	}

}