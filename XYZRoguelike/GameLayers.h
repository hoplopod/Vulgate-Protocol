#pragma once

#include "GameWorld.h"
#include "GameObject.h"
#include"LayerRenderingComponent.h"

namespace XYZRoguelike
{
	class Layers
	{
	public:
		Layers()
		{
			gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("layers_system");
			auto layer_render = gameObject->AddComponent<XYZEngine::LayerRenderingComponent>();
			layer_render->CreateNewNumLayer(4);
		}
		XYZEngine::GameObject* GetGameObject();

	private:
		XYZEngine::GameObject* gameObject;

	};
}
