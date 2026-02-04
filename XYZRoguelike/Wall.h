#pragma once

#include <GameWorld.h>
#include <ResourceSystem.h>
#include "GameObject.h"

namespace Roguelike
{
	class Wall
	{
	public:
		Wall(const HopEngine::Vector2Df position, int textureMapIndex);
	private:
		HopEngine::GameObject* gameObject;
	};
}

