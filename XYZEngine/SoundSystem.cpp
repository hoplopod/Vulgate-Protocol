#include "pch.h"
#include "SoundSystem.h"

HopEngine::SoundSystem* HopEngine::SoundSystem::Instance()
{
    static SoundSystem instance;
    return &instance;
}

void HopEngine::SoundSystem::Play_Sound(const std::string& name)
{ 
    auto it = audios.find(name);
    if (it != audios.end())
    {
        it->second->Play();
    }
    else LOG_ERROR("Failed to play sound " + name);
}

void HopEngine::SoundSystem::Subscribe_Sound(const std::string& name, AudioComponent* new_sound)
{
    audios.emplace(name, new_sound);
}

void HopEngine::SoundSystem::Unsubscribe_Sound(const std::string& name)
{
    auto it = audios.find(name);
    if (it != audios.end())
    {
        audios.erase(it);
    }
}
