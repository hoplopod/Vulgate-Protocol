#pragma once
#include "AudioComponent.h"
#include <map>

namespace HopEngine
{

	class SoundSystem
	{
	public:
		static SoundSystem* Instance();

		void Play_Sound(const std::string& name);

		void Subscribe_Sound(const std::string& name, AudioComponent* new_sound);
		void Unsubscribe_Sound(const std::string& name);

		void Reset();
	private:

		std::map<std::string, AudioComponent*> audios;

		SoundSystem() {}
		~SoundSystem() {}

		SoundSystem(SoundSystem const&) = delete;
		SoundSystem& operator= (SoundSystem const&) = delete;
	};

}
