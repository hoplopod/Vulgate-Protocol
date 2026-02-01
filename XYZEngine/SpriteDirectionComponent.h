#pragma once
#include "GameObject.h"
#include "MovementComponent.h"
#include "SpriteRendererComponent.h"

namespace HopEngine
{
	class SpriteDirectionComponent : public Component
	{
	public:
		SpriteDirectionComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;
	private:
		MovementComponent* move;
		SpriteRendererComponent* spriteRenderer;
	};
}
