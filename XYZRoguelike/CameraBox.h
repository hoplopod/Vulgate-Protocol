#pragma once

#include "CameraComponent.h"
#include "GameWorld.h"
#include "GameObject.h"
#include "Vector.h"

namespace Roguelike
{
	class CameraBox
	{
	public:
		CameraBox(const HopEngine::Vector2Df& position);
		HopEngine::GameObject* GetGameObject();

	private:
		HopEngine::GameObject* gameObject;
	};
}
