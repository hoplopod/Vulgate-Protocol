#include "GameLevel.h"
#include <assert.h>

namespace Roguelike {

	void LevelLoader::LevelLoadFromFile()
	{
		file.open("Resources/levels.config");
		std::string line;
		int y = 0, x = 0;

		while (std::getline(file, line)) {
			if (line.rfind("level ", 0) == 0) {
				auto level = std::stoi(line.substr(6, line.size() - 6));
				levels.emplace_back(Level());
				y = 0;
			}
			else {
				int x = 0;
				for (char c : line) {
					if (c != ' ') {
						levels.back().map_interior.emplace_back(std::make_pair(sf::Vector2i{ x, y }, CharToMapInteriorType(c)));
					}
					++x;
				}

			}
			++y;
		}
		file.close();
	}
	MapInterior LevelLoader::CharToMapInteriorType(char symbol)
	{
		MapInterior type = MapInterior::nothing;
		switch (symbol)
		{
		case '1':
			type = MapInterior::floor;
			break;
		case '2':
			type = MapInterior::wall;
			break;
		default:
			assert(false);
			break;
		}

		return type;
	}
}
