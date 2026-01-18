#include "pch.h"
#include "LayerRenderingComponent.h"

namespace XYZEngine{

LayerRenderingComponent::LayerRenderingComponent(GameObject* gameObject) : Component(gameObject)
{
}

void LayerRenderingComponent::Update(float deltaTime)
{
}

void LayerRenderingComponent::Render()
{
	for (int i = 0; i < layers.size(); ++i) {

		for (int j = 0; j < layers[i].size(); ++j) {
			if (layers[i][j] != nullptr) {
				RenderSystem::Instance()->Render(*layers[i][j]->GetSprite());
			}
		}
	}
}

void LayerRenderingComponent::CreateNewNumLayer(int new_num_layers)
{
	if (new_num_layers > num_layers) {
		num_layers = new_num_layers;
		layers.resize(num_layers);
	}
	
}

void LayerRenderingComponent::AddToLayer(int layer_num, SpriteRendererComponent* sprite)
{
	if (layer_num > -1 && layer_num < layers.size()) {
		layers[layer_num].push_back(sprite);
	}
	
}

}

