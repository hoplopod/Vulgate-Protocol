#pragma once

#include "Component.h"
#include "TransformComponent.h"
#include "SpriteRendererComponent.h"
#include <memory>

namespace XYZEngine {

	class BoneComponent : public Component
	{
	public:
		BoneComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		BoneComponent* AddChild(std::unique_ptr<BoneComponent> child, float new_length, float new_shift);

		void BoneTransform();

	private:
		XYZEngine::TransformComponent* transform;
		
		float shift = 0.f;
		float length = 0;
		BoneComponent* parent = nullptr;
		std::vector<std::unique_ptr<BoneComponent>> childrens;
	};

}
