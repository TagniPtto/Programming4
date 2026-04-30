#include "SDLSoundSystem.h"

void dae::SDLSoundSystem::LoadAudio(std::string fname)
{
    char* path = NULL;
    MIX_Audio* audio;
    SDL_asprintf(&path, "%s%s", SDL_GetBasePath(), fname.c_str());
    audio = MIX_LoadAudio(m_pMixer, path, false);
    if (!audio) {
        SDL_Log("Couldn't load %s: %s", path, SDL_GetError());
    }
    loadedAudio.push_back(audio);


    m_pTrack = MIX_CreateTrack(m_pMixer);
    if (!m_pTrack) {
        SDL_Log("Couldn't create a mixer track: %s", SDL_GetError());
    }


    SDL_free(path); 
}

void dae::SDLSoundSystem::UnloadAudio(const sound_id)
{
}

void dae::SDLSoundSystem::play(const sound_id id, const float)
{
    MIX_SetTrackAudio(m_pTrack, loadedAudio[id]);
    MIX_PlayTrack(m_pTrack, 0);
}

dae::SDLSoundSystem::SDLSoundSystem()
{
    if (!MIX_Init()) {
        SDL_Log("Couldn't init SDL_mixer library: %s", SDL_GetError());

    }
    m_pMixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    if (!m_pMixer) {
        SDL_Log("Couldn't create mixer on default device: %s", SDL_GetError());
    }

}

dae::SDLSoundSystem::~SDLSoundSystem()
{
    MIX_Quit();
}
