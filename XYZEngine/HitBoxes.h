#pragma once

#include <SFML/Graphics.hpp>

namespace HopEngine
{
	class ColliderComponent;
	struct HitBox
	{
	public:
		HitBox(ColliderComponent* newFirst, ColliderComponent* newSecond, sf::FloatRect newHitBoxRect) :
			first(newFirst), second(newSecond), HitBoxRect(newHitBoxRect) {
		};
	private:
		ColliderComponent* first;
		ColliderComponent* second;
		sf::FloatRect HitBoxRect;
	};
}