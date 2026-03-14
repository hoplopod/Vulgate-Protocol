// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Engine.h"
#include "ResourceSystem.h"
#include "DeveloperLevel.h"
#include "Matrix2D.h"

using namespace Roguelike;

int main()
{
	HopEngine::RenderSystem::Instance()->SetMainWindow(new sf::RenderWindow(sf::VideoMode(1280, 720), "Roguelike"));
	
	ResourceSystem::Instance()->LoadTexture("player", "Resources/Textures/ball.png");
	ResourceSystem::Instance()->LoadTextureMap("level_floors", "Resources/TextureMaps/Floor.png", { 16, 16 }, 49, false);
	ResourceSystem::Instance()->LoadTextureMap("level_walls", "Resources/TextureMaps/Wall.png", { 16, 16 }, 48, false);
	
	//Spine
	ResourceSystem::Instance()->LoadSpineFiles("player", "Resources/SpineData/Player/Player.atlas", "Resources/SpineData/Player/Player.json");

	//Debugging resources
	//ResourceSystem::Instance()->LoadSound("music", "Resources/Sounds/AppleEat.wav");
	ResourceSystem::Instance()->LoadTexture("bone", "Resources/TextureMaps/Bone.png", false);

	//Start
	auto developerLevel = std::make_shared<DeveloperLevel>();
	developerLevel->Start();

	HopEngine::Engine::Instance()->Run();

	return 0;
}
