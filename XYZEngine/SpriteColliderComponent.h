#pragma once

#include "ColliderComponent.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include <SFML/Graphics/Sprite.hpp>

namespace HopEngine
{
	class SpriteColliderComponent : public ColliderComponent
	{
	public:
		SpriteColliderComponent(GameObject* gameObject);
		~SpriteColliderComponent();

		void SetMapCollision(sf::FloatRect newMapBounds);
		void AddToMapCollision();

		void Update(float deltaTime) override;
		void Render() override;
	private:
		sf::FloatRect bounds_shift_for_a_map;
		const sf::Sprite* sprite;
	};
}

