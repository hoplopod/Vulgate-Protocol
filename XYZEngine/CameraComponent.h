#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "TransformComponent.h"

namespace HopEngine
{
	class CameraComponent : public Component
	{
	public:
		CameraComponent(GameObject* gameObject);
		~CameraComponent();

		void Update(float deltaTime) override;
		void Render() override;

		void SetWindow(sf::RenderWindow* newWindow);
		void ZoomBy(float newZoom);

		void SetShift(Vector2Df new_shift);
		void SetBaseResolution(int width, int height);
	private:
		TransformComponent* transform;
		sf::RenderWindow* window;
		sf::View* view;
		Vector2Df shift = { 0,0 };
	};
}