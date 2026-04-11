#pragma once

#include <iostream>
#include <array>
#include "Scene.h"
#include "Player.h"
#include "Baptist.h"
#include "Music.h"
#include "Floor.h"
#include "Wall.h"
#include "CameraBox.h"
#include "GameLayers.h"
#include "GameLevel.h"

using namespace HopEngine;

namespace Roguelike
{
	class DeveloperLevel : public Scene
	{
	public:
		void Start() override;
		void Restart() override;
		void Stop() override;

		std::vector<std::unique_ptr<Wall>> walls;
		std::vector<std::unique_ptr<Floor>> floors;

	private:
		std::unique_ptr<Player> player;
		std::unique_ptr<Baptist> baptist;
		std::shared_ptr<CameraBox> cameraBox;
		std::shared_ptr<Layers> layer_system;
		std::unique_ptr<Music> music;
		std::shared_ptr<LevelLoader> loader;

	};
}