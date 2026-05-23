#include "SDLSoundSystem.h"


void dae::SDLSoundSystem::Play(const sound_id id, const float volume)
{
    std::scoped_lock lock(m_mutex);
    m_eventQueue.push({id,volume});
}

void dae::SDLSoundSystem::Update()
{
    m_conditional_variable.notify_all();
}

void dae::SDLSoundSystem::ThreadProcess()
{
    while (!(!threadIsRunning && m_eventQueue.empty()))
    {

        std::unique_lock<std::mutex> lock(m_mutex);
        m_conditional_variable.wait(lock, [&]() { return !m_eventQueue.empty() || !threadIsRunning; });

        while (!m_eventQueue.empty()) {

            dae::SoundEvent event = m_eventQueue.front();
            MIX_SetTrackAudio(m_pTrack, m_loadedAudio[event.id]);
            MIX_SetTrackGain(m_pTrack, event.volume);
            MIX_PlayTrack(m_pTrack, 0);

            m_eventQueue.pop();
          
        }
    }
}

void dae::SDLSoundSystem::LoadAudio(std::string fname)
{
    char* path = NULL;
    MIX_Audio* audio;
    SDL_asprintf(&path, "%s%s", SDL_GetBasePath(), fname.c_str());
    audio = MIX_LoadAudio(m_pMixer, path, false);
    if (!audio) {
        SDL_Log("Couldn't load %s: %s", path, SDL_GetError());
    }
    m_loadedAudio.push_back(audio);

    SDL_free(path); 
}

void dae::SDLSoundSystem::UnloadAudio(const sound_id)
{
    std::erase(std::remove_if(m_loadedAudio.begin(), m_loadedAudio.end(), []() {}));
    MIX_DestroyAudio();
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
    
    m_worker = std::jthread(&SDLSoundSystem::ThreadProcess,this);
}

dae::SDLSoundSystem::~SDLSoundSystem()
{
    threadIsRunning = false;
    m_conditional_variable.notify_all();

    for (auto& audio : m_loadedAudio) {
        MIX_DestroyAudio(audio);
    }
    MIX_DestroyMixer(m_pMixer);
    MIX_DestroyTrack(m_pTrack);
    MIX_Quit();
}
