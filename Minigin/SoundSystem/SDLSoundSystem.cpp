#include "SDLSoundSystem.h"
#include <SDL3_mixer/SDL_mixer.h>

#include <cassert>

void dae::SDLSoundSystem::PlayAudio(const std::string& name, const float volume)
{
    {
    std::scoped_lock lock(m_mutex);
    m_eventQueue.push(SoundEvent(name, volume));
    }
    m_conditional_variable.notify_one();
}

void dae::SDLSoundSystem::PlayMusic(const std::string& name, const float volume)
{
    {
        std::scoped_lock lock(m_mutex);
        m_eventQueue.push(SoundEvent(name, volume,AudioType::Music));
    }
    m_conditional_variable.notify_one();
}

void dae::SDLSoundSystem::ThreadProcess()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_conditional_variable.wait(lock, [&]() { return !threadIsRunning || !m_eventQueue.empty(); });

        if (!threadIsRunning.load() && m_eventQueue.empty())
        {
            break;
        }

        const dae::SoundEvent event = m_eventQueue.front();
        m_eventQueue.pop();


        MIX_Audio* audio = m_loadedAudio[event.name];
        MIX_Track* track = nullptr;
        SDL_PropertiesID options = SDL_CreateProperties();


        if (!audio) continue;

        if (event.type == AudioType::Music) {
            track = m_pMusicTrack;
            SDL_SetNumberProperty(options, MIX_PROP_PLAY_LOOPS_NUMBER, -1);
        }
        if (event.type == AudioType::SFX) {
            track = m_pSfxTrack;
        }
        if (!track)continue;
       
        MIX_StopTrack(track, 0);
        MIX_SetTrackAudio(track, audio);
        MIX_SetTrackGain(track, event.volume);
        MIX_PlayTrack(track, options);
    }
}

void dae::SDLSoundSystem::LoadAudio(const std::string& fname, const std::string& name)
{
    std::scoped_lock lock(m_mutex);
    char* path = nullptr;
    MIX_Audio* audio;
    SDL_asprintf(&path, "%s%s", SDL_GetBasePath(), fname.c_str());
    audio = MIX_LoadAudio(m_pMixer, path, false);
    if (!audio) {
        SDL_Log("Couldn't load %s: %s", path, SDL_GetError());
    }
    m_loadedAudio.insert({ name ,audio });
    SDL_free(path); 
}

void dae::SDLSoundSystem::UnloadAudio(const std::string& name)
{
    std::scoped_lock lock(m_mutex);
    auto audio = m_loadedAudio[name];
    if (audio) {
        MIX_DestroyAudio(audio);
        m_loadedAudio.erase(name);
    }
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

    m_pSfxTrack = MIX_CreateTrack(m_pMixer);
    if (!m_pSfxTrack) {
        SDL_Log("Couldn't create a mixer track: %s", SDL_GetError());
    }
    m_pMusicTrack = MIX_CreateTrack(m_pMixer);
    if (!m_pMusicTrack) {
        SDL_Log("Couldn't create a mixer track: %s", SDL_GetError());
    }
    
    m_worker = std::thread(&SDLSoundSystem::ThreadProcess,this);
}

dae::SDLSoundSystem::~SDLSoundSystem()
{
    threadIsRunning = false;
    m_conditional_variable.notify_all();
    if (m_worker.joinable()) {
        m_worker.join();
    }

    MIX_Quit();
}
