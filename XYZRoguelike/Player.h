#pragma once

#include "CameraComponent.h"
#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include "InputComponent.h"
#include "GameObject.h"
#include "Vector.h"

namespace Roguelike
{
	class Player
	{
	public:
		Player(const HopEngine::Vector2Df& position);
		HopEngine::GameObject* GetGameObject();

	private:
		HopEngine::GameObject* gameObject;

	};
}