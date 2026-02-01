#pragma once

#include "GameWorld.h"
#include "GameObject.h"
#include"LayerRenderingComponent.h"

namespace Roguelike
{
	class Layers
	{
	public:
		Layers()
		{
			gameObject = HopEngine::GameWorld::Instance()->CreateGameObject("layers_system");
			auto layer_render = gameObject->AddComponent<HopEngine::LayerRenderingComponent>();
			layer_render->CreateNewNumLayer(4);
		}
		HopEngine::GameObject* GetGameObject();

	private:
		HopEngine::GameObject* gameObject;

	};
}
