#include "pch.h"
#include "InputComponent.h"
#include "Logger.h"

namespace HopEngine
{
	InputComponent::InputComponent(GameObject* gameObject) : Component(gameObject) {}

	void InputComponent::Update(float deltaTime)
	{
		//move
		verticalAxis = 0.f;
		horizontalAxis = 0.f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			horizontalAxis += 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			horizontalAxis -= 1.0f;
		}

		//player block
		playerBlock = false;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !wasMousePressedRight) {
			playerBlock = true;
		}
		wasMousePressedRight = sf::Mouse::isButtonPressed(sf::Mouse::Right);

		//player kick
		playerKick = false;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !wasMousePressedLeft) {
			playerKick = true;
		}
		wasMousePressedLeft = sf::Mouse::isButtonPressed(sf::Mouse::Left);

		//blade switch
		switchBlade = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !wasSpacePressed) {
			switchBlade = true;
		}
		wasSpacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

		//player stab
		playerStab = false;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && !wasMousePressedMiddle) {
			playerStab = true;
		}
		wasMousePressedMiddle = sf::Mouse::isButtonPressed(sf::Mouse::Middle);

	}
	void InputComponent::Render()
	{

	}

	float InputComponent::GetHorizontalAxis() const
	{
		return horizontalAxis;
	}
	float InputComponent::GetVerticalAxis() const
	{
		return verticalAxis;
	}

	bool InputComponent::GetSwitchedBlade() const
	{
		return switchBlade;
	}

	bool InputComponent::GetPlayerKick() const
	{
		return playerKick;
	}

	bool InputComponent::GetPlayerBlock() const
	{
		return playerBlock;
	}

	bool InputComponent::GetPlayerStab() const
	{
		return playerStab;
	}

}