#include "Audio.h"

Roguelike::Music::Music(const std::string& soundName)
{
	gameObject = HopEngine::GameWorld::Instance()->CreateGameObject("Music: " + soundName);
	auto music = gameObject->AddComponent<HopEngine::AudioComponent>();
	music->SetAudio(*HopEngine::ResourceSystem::Instance()->GetSound(soundName));
	music->SetLoop(true);

	HopEngine::SoundSystem::Instance()->Subscribe_Sound(gameObject->GetName(), music);
}

Roguelike::Sound::Sound(const std::string& soundName)
{
	gameObject = HopEngine::GameWorld::Instance()->CreateGameObject("Music: " + soundName);
	auto sound = gameObject->AddComponent<HopEngine::AudioComponent>();
	sound->SetAudio(*HopEngine::ResourceSystem::Instance()->GetSound(soundName));
	sound->SetLoop(false);

	HopEngine::SoundSystem::Instance()->Subscribe_Sound(gameObject->GetName(), sound);
}
