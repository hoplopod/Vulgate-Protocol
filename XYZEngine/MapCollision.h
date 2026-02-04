#pragma once

#include <SFML/Graphics.hpp>

namespace HopEngine
{
	class ColliderComponent;
	struct MapCollision
	{
	public:
		MapCollision(ColliderComponent* newFirst, ColliderComponent* newSecond, sf::FloatRect newCollisionRect) :
			first(newFirst), second(newSecond), collisionRect(newCollisionRect) {
		};
	private:
		ColliderComponent* first;
		ColliderComponent* second;
		sf::FloatRect collisionRect;
	};
}