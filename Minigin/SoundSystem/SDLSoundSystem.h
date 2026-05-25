#pragma once

#include "ISoundSystem.h"


#include <unordered_map>
#include <queue>
#include <thread>
#include <condition_variable>
#include <mutex>

#include <SDL3_mixer/SDL_mixer.h>

namespace dae
{

	class SDLSoundSystem final : public ISoundSystem {
	private:
		MIX_Mixer* m_pMixer = NULL;
		MIX_Track* m_pTrack = NULL;

		std::thread m_worker;
		std::mutex m_mutex;
		std::condition_variable m_conditional_variable;
		std::unordered_map<std::string,MIX_Audio*> m_loadedAudio;
		std::queue<SoundEvent> m_eventQueue;


		std::atomic_bool threadIsRunning = true;
	public:
		void ThreadProcess();
		void LoadAudio(const std::string& path , const std::string& name) override;
		void UnloadAudio(const std::string& name) override;
		void Play(const std::string& name, const float volume)  override;
		SDLSoundSystem();
		~SDLSoundSystem();
	};
}