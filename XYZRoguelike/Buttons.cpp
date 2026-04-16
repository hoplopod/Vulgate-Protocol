#include "Buttons.h"

Roguelike::Start_Button::Start_Button()
{
	button_shape.setSize({ 300.f, 100.f });

	button_shape.setOrigin(button_shape.getSize() / 2.f);

	auto& window = RenderSystem::Instance()->GetMainWindow();
	sf::Vector2u winSize = window.getSize();

	button_shape.setPosition(winSize.x / 2.f, winSize.y / 2.f + 50);

	button_shape.setTexture(ResourceSystem::Instance()->GetTextureCopy("start_button"));
}

void Roguelike::Start_Button::Action()
{
	GameManager::Instance()->setState(GameState::Playing);
}

Roguelike::Exit_Button::Exit_Button()
{
	button_shape.setSize({ 300.f, 100.f });

	button_shape.setOrigin(button_shape.getSize() / 2.f);

	auto& window = RenderSystem::Instance()->GetMainWindow();
	sf::Vector2u winSize = window.getSize();

	button_shape.setPosition(winSize.x / 2.f, winSize.y / 2.f + 150);

	button_shape.setTexture(ResourceSystem::Instance()->GetTextureCopy("exit_button"));
}

void Roguelike::Exit_Button::Action()
{
	GameManager::Instance()->setState(GameState::Close);
}
