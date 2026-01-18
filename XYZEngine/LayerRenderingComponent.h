#pragma once
#include "Component.h"
#include "GameObject.h"
#include "GameWorld.h"
#include "RenderSystem.h"
#include "SpriteRendererComponent.h"

namespace XYZEngine {

	class LayerRenderingComponent : public Component {

	public:
		LayerRenderingComponent(GameObject* gameObject);
		~LayerRenderingComponent() = default;

		void Update(float deltaTime) override;
		void Render() override;

		void CreateNewNumLayer(int new_num_layers);
		void AddToLayer(int layer_num, SpriteRendererComponent* sprite);

	private:
		std::vector<std::vector<SpriteRendererComponent*>> layers;
		int num_layers = 0;
	};

}

