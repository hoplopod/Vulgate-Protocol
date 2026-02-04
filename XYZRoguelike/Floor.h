#pragma once

#include <GameWorld.h>
#include <SpriteRendererComponent.h>
#include <ResourceSystem.h>
#include "GameObject.h"

namespace Roguelike
{
	class Floor
	{
	public:
		Floor(const HopEngine::Vector2Df& position, int textureMapIndex);
	private:
		HopEngine::GameObject* gameObject;
	};
}

