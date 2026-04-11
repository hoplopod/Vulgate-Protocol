#pragma once

#include "Component.h"
#include <SFML/Window.hpp> 

namespace HopEngine
{
	class InputComponent : public Component
	{
	public:
		InputComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		float GetHorizontalAxis() const;
		float GetVerticalAxis() const;

		bool GetSwitchedBlade() const;
		bool GetPlayerKick() const;
		bool GetPlayerBlock() const;
		bool GetPlayerStab() const;

	private:
		float horizontalAxis = 0.f;
		float verticalAxis = 0.f;

		bool playerBlock = false;
		bool switchBlade = false;
		bool playerKick = false;
		bool playerStab = false;

		bool wasMousePressedLeft = false;
		bool wasMousePressedRight = false;
		bool wasSpacePressed = false;
		bool wasMousePressedMiddle = false;

	};

	
}