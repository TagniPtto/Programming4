#include "SDLLoggingSoundSystem.h"

void dae::SDLLoggingSoundSystem::LoadAudio(const std::string& path, const std::string& name)
{
	SDLSoundSystem::LoadAudio(path, name);
}

void dae::SDLLoggingSoundSystem::UnloadAudio(const std::string& name)
{
	SDLSoundSystem::UnloadAudio(name);
}

void dae::SDLLoggingSoundSystem::Play(const std::string & name, const float volume)
{
	SDLSoundSystem::Play(name , volume);
}
