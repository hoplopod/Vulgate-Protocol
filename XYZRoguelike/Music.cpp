#include "Music.h"

Music::Music(const std::string& soundName)
{
	auto gameObject = HopEngine::GameWorld::Instance()->CreateGameObject("Music: " + soundName);
	auto music = gameObject->AddComponent<HopEngine::AudioComponent>();
	music->SetAudio(*HopEngine::ResourceSystem::Instance()->GetSound(soundName));
	music->SetLoop(false);
	music->Play();
}
