#pragma once

#include "CameraComponent.h"
#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include "InputComponent.h"
#include "GameObject.h"
#include "Vector.h"
#include "BoneComponent.h"

namespace XYZRoguelike
{
	class Player
	{
	public:
		Player(const XYZEngine::Vector2Df& position);
		XYZEngine::GameObject* GetGameObject();

		void createSkeleton();
	private:
		XYZEngine::GameObject* gameObject;

	};
}