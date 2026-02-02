#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "GameWorld.h"

namespace Roguelike {

	enum class MapInterior {
		nothing,
		wall,
		floor
	};

	struct Level {
		std::vector< std::pair<sf::Vector2i, MapInterior>> map_interior;
	};

	class LevelLoader {
	public:
		LevelLoader() = default;
		~LevelLoader() = default;

		void LevelLoadFromFile();

		Level& GetLevel(int i) {
			return levels.at(i);
		}
	
	private:
		std::ifstream file;
		std::vector<Level> levels;

		static MapInterior CharToMapInteriorType(char symbol);
	};

}
