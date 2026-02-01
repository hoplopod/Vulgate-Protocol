#include "pch.h"
#include "AudioComponent.h"

HopEngine::AudioComponent::AudioComponent(GameObject* gameObject)
	: Component(gameObject)
{
	sound = new sf::Sound();
}

HopEngine::AudioComponent::~AudioComponent()
{
	sound->stop();
	delete sound;
}

void HopEngine::AudioComponent::Update(float deltaTime)
{
}

void HopEngine::AudioComponent::Render()
{
}

void HopEngine::AudioComponent::SetAudio(const sf::SoundBuffer& audio)
{
	sound->setBuffer(audio);
}

void HopEngine::AudioComponent::SetLoop(bool loop)
{
	sound->setLoop(loop);
}

void HopEngine::AudioComponent::SetVolume(float volume)
{
	sound->setVolume(volume);
}

void HopEngine::AudioComponent::Play()
{
	if (sound->getStatus() != sf::SoundSource::Playing)
	{
		sound->play();
	}
}

void HopEngine::AudioComponent::Stop()
{
	sound->stop();
}

void HopEngine::AudioComponent::Pause()
{
	sound->pause();
}

void HopEngine::AudioComponent::Resume()
{
	if (sound->getStatus() != sf::SoundSource::Playing)
	{
		sound->play();
	}
}
