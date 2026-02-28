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
	
	ResourceSystem::Instance()->LoadTextureMap("player", "Resources/TextureMaps/Player.png", { 48, 63 }, 4, false);
	ResourceSystem::Instance()->LoadTextureMap("level_floors", "Resources/TextureMaps/Floor.png", { 16, 16 }, 49, false);
	ResourceSystem::Instance()->LoadTextureMap("level_walls", "Resources/TextureMaps/Wall.png", { 16, 16 }, 48, false);
	
	//Spine
	ResourceSystem::Instance()->LoadSpineFiles("player", "Resources/SpineData/Player/Player.atlas", "Resources/SpineData/Player/Player.json");
	//ResourceSystem::Instance()->LoadSpineFiles("player", "C:/Users/hoplo/Desktop/SpineTry/SpineTry/data/sack-pma.atlas", "C:/Users/hoplo/Desktop/SpineTry/SpineTry/data/sack-pro.json");

	//Player skeleton
	//head
	ResourceSystem::Instance()->LoadTexture("player_head", "Resources/Textures/Player/Player_head.png", false);
	//body
	ResourceSystem::Instance()->LoadTexture("player_body", "Resources/Textures/Player/Player_body.png", false);
	//Arms
	//left
	//front
	ResourceSystem::Instance()->LoadTexture("player_shoulder_left_front", "Resources/Textures/Player/Player_shoulder_left_front.png", false);
	ResourceSystem::Instance()->LoadTexture("player_forearm_left_front", "Resources/Textures/Player/Player_forearm_left_front.png", false);
	ResourceSystem::Instance()->LoadTexture("player_brush_left_front", "Resources/Textures/Player/Player_brush_left_front.png", false);
	//back
	ResourceSystem::Instance()->LoadTexture("player_shoulder_left_back", "Resources/Textures/Player/Player_shoulder_left_back.png", false);
	ResourceSystem::Instance()->LoadTexture("player_forearm_left_back", "Resources/Textures/Player/Player_forearm_left_back.png", false);
	ResourceSystem::Instance()->LoadTexture("player_brush_left_back", "Resources/Textures/Player/Player_brush_left_back.png", false);
	//right
	//front
	ResourceSystem::Instance()->LoadTexture("player_shoulder_right_front", "Resources/Textures/Player/Player_shoulder_right_front.png", false);
	ResourceSystem::Instance()->LoadTexture("player_forearm_right_front", "Resources/Textures/Player/Player_forearm_right_front.png", false);
	ResourceSystem::Instance()->LoadTexture("player_brush_right_front", "Resources/Textures/Player/Player_brush_right_front.png", false);
	//back
	ResourceSystem::Instance()->LoadTexture("player_shoulder_right_back", "Resources/Textures/Player/Player_shoulder_right_back.png", false);
	ResourceSystem::Instance()->LoadTexture("player_forearm_right_back", "Resources/Textures/Player_forearm_right_back.png", false);
	ResourceSystem::Instance()->LoadTexture("player_brush_right_back", "Resources/Textures/Player/Player_brush_right_back.png", false);
	//Legs
	//front
	ResourceSystem::Instance()->LoadTexture("player_hip_front", "Resources/Textures/Player/Player_hip_front.png", false);
	ResourceSystem::Instance()->LoadTexture("player_shin_front", "Resources/Textures/Player/Player_shin_front.png", false);
	ResourceSystem::Instance()->LoadTexture("player_foot_front", "Resources/Textures/Player/Player_foot_front.png", false);
	//back
	ResourceSystem::Instance()->LoadTexture("player_hip_back", "Resources/Textures/Player/Player_hip_back.png", false);
	ResourceSystem::Instance()->LoadTexture("player_shin_back", "Resources/Textures/Player/Player_shin_back.png", false);
	ResourceSystem::Instance()->LoadTexture("player_foot_back", "Resources/Textures/Player/Player_foot_back.png", false);

	//Debugging resources
	//ResourceSystem::Instance()->LoadSound("music", "Resources/Sounds/AppleEat.wav");
	ResourceSystem::Instance()->LoadTexture("bone", "Resources/TextureMaps/Bone.png", false);

	//Start
	auto developerLevel = std::make_shared<DeveloperLevel>();
	developerLevel->Start();

	HopEngine::Engine::Instance()->Run();

	return 0;
}
