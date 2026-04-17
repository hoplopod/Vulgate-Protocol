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
	
	//Map
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

	//Audio
	ResourceSystem::Instance()->LoadSound("fight", "Resources/Audio/fight.wav");
	ResourceSystem::Instance()->LoadSound("enemy hit", "Resources/Audio/enemy hit.wav");
	ResourceSystem::Instance()->LoadSound("player hit", "Resources/Audio/player hit.wav");
	ResourceSystem::Instance()->LoadSound("sword clash", "Resources/Audio/sword clash.wav");
	ResourceSystem::Instance()->LoadSound("block", "Resources/Audio/block.wav");

	//Start

	GameManager::Instance()->Run();

	return 0;
}
