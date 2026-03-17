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

		//switch blade
		switchBlade = false;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !wasMousePressedRight) {
			switchBlade = true;
		}
		wasMousePressedRight = sf::Mouse::isButtonPressed(sf::Mouse::Right);

		//Kick
		playerKick = false;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !wasMousePressedLeft) {
			playerKick = true;
		}
		wasMousePressedLeft = sf::Mouse::isButtonPressed(sf::Mouse::Left);
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

}