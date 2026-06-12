#include "SDLLoggingSoundSystem.h"

void dae::SDLLoggingSoundSystem::LoadAudio(const std::string& path, const std::string& name)
{
	SDLSoundSystem::LoadAudio(path, name);
}

void dae::SDLLoggingSoundSystem::UnloadAudio(const std::string& name)
{
	SDLSoundSystem::UnloadAudio(name);
}

void dae::SDLLoggingSoundSystem::PlayAudio(const std::string & name, const float volume)
{
	SDLSoundSystem::PlayAudio(name , volume);
}

void dae::SDLLoggingSoundSystem::PlayMusic(const std::string& name, const float volume)
{
	SDLSoundSystem::PlayMusic(name, volume);
}
