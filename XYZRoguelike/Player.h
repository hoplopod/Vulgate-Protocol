#pragma once

#include "CameraComponent.h"
#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include "InputComponent.h"
#include "GameObject.h"
#include "Vector.h"
#include "BoneComponent.h"

namespace Roguelike
{
	class Player
	{
	public:
		Player(const HopEngine::Vector2Df& position);
		HopEngine::GameObject* GetGameObject();

		void createSkeleton();
	private:
		HopEngine::GameObject* gameObject;

	};
}