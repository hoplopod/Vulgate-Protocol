// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include "StateManager.h"
#include "ResourceSystem.h"
#include "Matrix2D.h"

using namespace Roguelike;

int main()
{
	HopEngine::RenderSystem::Instance()->SetMainWindow(new sf::RenderWindow(sf::VideoMode(1280, 720), "Roguelike"));
	
	ResourceSystem::Instance()->LoadTextureMap("level_floors", "Resources/TextureMaps/floor vulgata.png", { 32, 32 }, 5, false);
	ResourceSystem::Instance()->LoadTextureMap("level_walls", "Resources/TextureMaps/Floor.png", { 16, 16 }, 49, false);
	
	//Spine
	ResourceSystem::Instance()->LoadSpineFiles("player", "Resources/SpineData/Player/Player.atlas", "Resources/SpineData/Player/Player.json");
	ResourceSystem::Instance()->LoadSpineFiles("baptist", "Resources/SpineData/Baptist/Baptist.atlas", "Resources/SpineData/Baptist/Baptist.json");

	//Logo
	ResourceSystem::Instance()->LoadTexture("logo", "Resources/Textures/logo vulgata.png");

	//Buttons
	ResourceSystem::Instance()->LoadTexture("start_button", "Resources/Textures/Buttons/start button.png");
	ResourceSystem::Instance()->LoadTexture("exit_button", "Resources/Textures/Buttons/exit button.png");

	//Start

	GameManager::Instance()->Run();

	return 0;
}
