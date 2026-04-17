#include "DeveloperLevel.h"

using namespace HopEngine;

namespace Roguelike
{
	void DeveloperLevel::Start()
	{
		layer_system = std::make_unique<Layers>();

		loader = std::make_unique<LevelLoader>();
		loader->LevelLoadFromFile();
		auto gameLevel = loader->GetLevel(0);

		for (int i = 0; i < gameLevel.map_interior.size(); ++i) {
			switch (gameLevel.map_interior[i].second)
			{
			case MapInterior::edge_left:
				floors.push_back(std::make_unique<Floor>(std::forward<HopEngine::Vector2Df>(
					{ gameLevel.map_interior[i].first.x * 128.f, gameLevel.map_interior[i].first.y * 128.f }), std::forward<int>(3)));
				break;
			case MapInterior::ledge_left:
				floors.push_back(std::make_unique<Floor>(std::forward<HopEngine::Vector2Df>(
					{ gameLevel.map_interior[i].first.x * 128.f, gameLevel.map_interior[i].first.y * 128.f }), std::forward<int>(4)));
				break;
			case MapInterior::block:
				floors.push_back(std::make_unique<Floor>(std::forward<HopEngine::Vector2Df>(
					{ gameLevel.map_interior[i].first.x * 128.f, gameLevel.map_interior[i].first.y * 128.f }), std::forward<int>(0)));
				break;
			case MapInterior::ledge_right:
				floors.push_back(std::make_unique<Floor>(std::forward<HopEngine::Vector2Df>(
					{ gameLevel.map_interior[i].first.x * 128.f, gameLevel.map_interior[i].first.y * 128.f }), std::forward<int>(1)));
				break;
			case MapInterior::edge_right:
				floors.push_back(std::make_unique<Floor>(std::forward<HopEngine::Vector2Df>(
					{ gameLevel.map_interior[i].first.x * 128.f, gameLevel.map_interior[i].first.y * 128.f }), std::forward<int>(2)));
				break;
			case MapInterior::wall:
				walls.push_back(std::make_unique<Wall>(std::forward<HopEngine::Vector2Df>(
					{ gameLevel.map_interior[i].first.x * 128.f, gameLevel.map_interior[i].first.y * 128.f }), std::forward<int>(48)));
				break;
			case MapInterior::nothing:
				break;
			default:
				break;
			}
		}

		
		cameraBox = std::make_unique<CameraBox>(std::forward<HopEngine::Vector2Df>({ 1500, 64 }));
		player = std::make_unique<Player>(std::forward<HopEngine::Vector2Df>({ 1300, 64}));
		baptist = std::make_unique<Baptist>(std::forward<HopEngine::Vector2Df>({ 1800, 64 }));
		
		music.push_back(std::make_unique<Music>("fight"));
	}
	void DeveloperLevel::Restart()
	{
		Stop();
		Start();
	}
	void DeveloperLevel::Stop() 
	{
		GameWorld::Instance()->Clear();
	}
}