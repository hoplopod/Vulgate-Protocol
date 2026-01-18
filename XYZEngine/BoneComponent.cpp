#include "pch.h"
#include "BoneComponent.h"

namespace XYZEngine {

	BoneComponent::BoneComponent(GameObject* gameObject) : Component(gameObject) {

		transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
	}

	BoneComponent* BoneComponent::AddChild(std::unique_ptr<BoneComponent> child, float new_length, float new_shift)
	{
		child->transform->SetParent(transform);
		child->shift = new_shift;
		child->length = new_length;
		child->parent = this;
		childrens.push_back(std::move(child));
		return childrens.back().get();
	}

	void BoneComponent::BoneTransform()
	{
		Vector2Df parentWorldPos = parent->transform->GetWorldPosition();
		float parentLocalAngle = parent->transform->GetLocalRotation();
		float pi = 3.1415926535;

		Vector2Df localPosition;
		localPosition.x = sin(parentLocalAngle * pi / 180) * length + shift;
		localPosition.y = cos(parentLocalAngle * pi / 180) * length;

		transform->SetWorldPosition(parentWorldPos.x + localPosition.x, parentWorldPos.y - localPosition.y);

	}

	void BoneComponent::Update(float deltaTime)
	{
		for (auto& child : childrens) {
			child->BoneTransform();
		}

	}

	void BoneComponent::Render()
	{
	}

}