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

		int width = 15;
		int height = 15;

		//for (int y = 0; y < height + 1; y++)
		//{
		//	for (int x = 0; x < width + 1; x++)
		//	{
		//		//if not wall place
		//		if (x != 0 && x != width && y != 0 && y != height)
		//		{
		//			floors.push_back(std::make_unique<Floor>(std::forward<HopEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(0)));
		//		}

		//		//if left-bottom corner
		//		if (x == 0 && y == 0)
		//		{
		//			walls.push_back(std::make_unique<Wall>(std::forward<HopEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(25)));
		//		}

		//		//if right-bottom corner
		//		if (x == width && y == 0)
		//		{
		//			walls.push_back(std::make_unique<Wall>(std::forward<HopEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(27)));
		//		}

		//		//if left-top corner
		//		if (x == 0 && y == height)
		//		{
		//			walls.push_back(std::make_unique<Wall>(std::forward<HopEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(1)));
		//		}

		//		//if right-top corner
		//		if (x == width && y == height)
		//		{
		//			walls.push_back(std::make_unique<Wall>(std::forward<HopEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(3)));
		//		}

		//		//if left (not corner)
		//		if (x == 0 && y != height && y != 0)
		//		{
		//			floors.push_back(std::make_unique<Floor>(std::forward<HopEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(18)));
		//			walls.push_back(std::make_unique<Wall>(std::forward<HopEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(12)));
		//		}

		//		//if right (not corner)
		//		if (x == width && y != height && y != 0)
		//		{
		//			floors.push_back(std::make_unique<Floor>(std::forward<HopEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(19)));
		//			walls.push_back(std::make_unique<Wall>(std::forward<HopEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(12)));
		//		}

		//		//if bottom (not corner)
		//		if (y == 0 && x != width && x != 0)
		//		{
		//			walls.push_back(std::make_unique<Wall>(std::forward<HopEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(38)));
		//		}

		//		//if top (not corner)
		//		if (y == height && x != width && x != 0)
		//		{
		//			walls.push_back(std::make_unique<Wall>(std::forward<HopEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(38)));
		//		}
		//	}
		//}

		// Maze Generator
		//MazeGenerator mazeGenerator(width, height, this);
		//mazeGenerator.Generate(); 

		player = std::make_unique<Player>(std::forward<HopEngine::Vector2Df>({ 250, 200}));
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