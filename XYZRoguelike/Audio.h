#pragma once

#include <GameObject.h>
#include <GameWorld.h>
#include <AudioComponent.h>
#include <ResourceSystem.h>
#include "SoundSystem.h"

namespace Roguelike {

	class Music
	{
	public:
		Music(const std::string& soundName);
	private:
		HopEngine::GameObject* gameObject;
	};

	class Sound {
	public:
		Sound(const std::string& soundName);
	private:
		HopEngine::GameObject* gameObject;
	};
}

