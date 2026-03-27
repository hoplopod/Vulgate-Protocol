#include "DeveloperLevel.h"
#include "Wall.h"
#include "MazeGenerator.h"

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
			case MapInterior::wall:
				walls.push_back(std::make_unique<Wall>(std::forward<HopEngine::Vector2Df>(
					{ gameLevel.map_interior[i].first.x * 128.f, gameLevel.map_interior[i].first.y * 128.f }), std::forward<int>(10)));
				break;
			case MapInterior::floor:
				floors.push_back(std::make_unique<Floor>(std::forward<HopEngine::Vector2Df>(
					{ gameLevel.map_interior[i].first.x * 128.f, gameLevel.map_interior[i].first.y * 128.f }), std::forward<int>(0)));
				break;
			case MapInterior::nothing:
				break;
			default:
				break;
			}
		}
		cameraBox = std::make_unique<CameraBox>(std::forward<HopEngine::Vector2Df>({ 800, 64 }));
		player = std::make_unique<Player>(std::forward<HopEngine::Vector2Df>({ 700, 64}));
		
		//music = std::make_unique<Music>("music");
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