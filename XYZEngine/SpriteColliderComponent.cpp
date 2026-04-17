#include "pch.h"
#include "SpriteColliderComponent.h"

namespace HopEngine
{
	SpriteColliderComponent::SpriteColliderComponent(GameObject* gameObject) : ColliderComponent(gameObject)
	{
		auto spriteRenderer = gameObject->GetComponent<SpriteRendererComponent>();
		if (spriteRenderer == nullptr)
		{
			std::cout << "SpriteRenderer required to SpriteCollider." << std::endl;
			gameObject->RemoveComponent(this);
			return;
		}

		sprite = gameObject->GetComponent<SpriteRendererComponent>()->GetSprite();
		TriggerSystem::Instance()->Subscribe_HitBoxes(this);
	}
	SpriteColliderComponent::~SpriteColliderComponent()
	{
		if (&bounds != nullptr)
		{
			std::destroy_at(&bounds);
		}
		TriggerSystem::Instance()->Unsubscribe_HitBoxes(this);
	}

	void SpriteColliderComponent::SetMapCollision(sf::FloatRect newMapBounds) {
		bounds_shift_for_a_map = newMapBounds;
		map_bounds = { 0,0,1,1};
	}

	void SpriteColliderComponent::AddToMapCollision() {
		TriggerSystem::Instance()->Subscribe_Map_Collision(this);
	}

	void SpriteColliderComponent::Update(float deltaTime)
	{
		bounds = sprite->getGlobalBounds();
		if (map_bounds.height != 0 && map_bounds.width != 0) {
			map_bounds = { bounds.left + bounds_shift_for_a_map.left, bounds.top + bounds_shift_for_a_map.top, bounds.width + bounds_shift_for_a_map.width,  bounds.height + bounds_shift_for_a_map.height };
		}
	}
	void SpriteColliderComponent::Render()
	{
		/*if (map_bounds.height != 0 && map_bounds.width != 0) {
			sf::RectangleShape rectangle(sf::Vector2f(map_bounds.width, map_bounds.height));
			rectangle.setPosition(map_bounds.left, map_bounds.top);
			rectangle.setFillColor(sf::Color::Transparent);
			rectangle.setOutlineColor(sf::Color::White);
			rectangle.setOutlineThickness(3);

			RenderSystem::Instance()->Render(rectangle);
		}*/

	}
}