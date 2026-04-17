#pragma once

#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include "InputComponent.h"
#include "GameObject.h"
#include "Vector.h"
#include <PlayerSpineComponent.h>
#include "UiComponent.h"

namespace Roguelike
{
	class Player
	{
	public:
		Player(const HopEngine::Vector2Df& position);
		HopEngine::GameObject* GetGameObject();

	private:
		HopEngine::GameObject* gameObject;
		std::map<int, std::pair < spine::String, std::pair<int, bool >> > createAnimations();
	};
}