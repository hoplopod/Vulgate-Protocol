#include "pch.h"
#include "DebuggingSystem.h"


void HopEngine::DebuggingSystem::Update()
{
	//world line
	sf::RectangleShape rectangle(sf::Vector2f(300, 2));
	rectangle.setPosition(0, 0);
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineColor(sf::Color::White);
	rectangle.setOutlineThickness(3);

	RenderSystem::Instance()->Render(rectangle);
}

