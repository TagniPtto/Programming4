#include "SDLSoundSystem.h"


void dae::SDLSoundSystem::Play(const std::string& name, const float volume)
{
    {
    std::scoped_lock lock(m_mutex);
    m_eventQueue.push(SoundEvent(name, volume));
    }
    m_conditional_variable.notify_one();
}

void dae::SDLSoundSystem::ThreadProcess()
{
    //while (true)
    //{
    //    std::unique_lock<std::mutex> lock(m_mutex);
    //    m_conditional_variable.wait(lock, [&]() { return !threadIsRunning.load() || !m_eventQueue.empty(); });


    //    if (!threadIsRunning.load() && m_eventQueue.empty())
    //    {
    //        break;
    //    }

    //    const dae::SoundEvent event = m_eventQueue.front();
    //    m_eventQueue.pop();
    //    MIX_Audio* audio = m_loadedAudio[event.name];

    //    if (audio) {
    //        MIX_StopTrack(m_pTrack, 0);
    //        MIX_SetTrackAudio(m_pTrack, audio);
    //        MIX_SetTrackGain(m_pTrack, event.volume);
    //        MIX_PlayTrack(m_pTrack, 0);
    //    }

    //}
    while (true)
    {
        SoundEvent event{ "", 0.0f };
        MIX_Audio* audio = nullptr;
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_conditional_variable.wait(lock, [&]() {
                return !threadIsRunning.load() || !m_eventQueue.empty();
                });
            if (!threadIsRunning.load() && m_eventQueue.empty())
                break;
            event = m_eventQueue.front();
            m_eventQueue.pop();

            auto it = m_loadedAudio.find(event.name);
            if (it != m_loadedAudio.end())
                audio = it->second;
        }
        // Lock released here
        if (audio) {
            MIX_StopTrack(m_pTrack, 0);
            MIX_SetTrackAudio(m_pTrack, audio);
            MIX_SetTrackGain(m_pTrack, event.volume);
            MIX_PlayTrack(m_pTrack, 0);
        }
    }
}

void dae::SDLSoundSystem::LoadAudio(const std::string& fname, const std::string& name)
{
    std::scoped_lock lock(m_mutex);

    char* path = NULL;
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

    m_pTrack = MIX_CreateTrack(m_pMixer);
    if (!m_pTrack) {
        SDL_Log("Couldn't create a mixer track: %s", SDL_GetError());
    }
    
    m_worker = std::thread(&SDLSoundSystem::ThreadProcess,this);
}

dae::SDLSoundSystem::~SDLSoundSystem()
{
    threadIsRunning.store(false);
    m_conditional_variable.notify_all();
    m_worker.join();

    MIX_StopTrack(m_pTrack,0);

    for (auto& [name, audio] : m_loadedAudio)
    {
        if (audio) MIX_DestroyAudio(audio);
    }

    m_loadedAudio.clear();

    if (m_pTrack)
    {
        MIX_DestroyTrack(m_pTrack);
    }


    if (m_pMixer)
    {
        MIX_DestroyMixer(m_pMixer);
    }

    
    MIX_Quit();
}
