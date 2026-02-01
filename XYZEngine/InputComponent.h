#pragma once

#include "Component.h"
#include <SFML/Window.hpp> 

namespace HopEngine
{
	enum class CharacterMoveState {
		Stand = -1,
		Walk_Right = 0,
		Walk_Left = 1
	};

	class InputComponent : public Component
	{
	public:
		InputComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		CharacterMoveState GetPlayerMoveState() const {
			return playerMoveState;
		}

	private:
		CharacterMoveState playerMoveState = CharacterMoveState::Stand;
	};

	
}