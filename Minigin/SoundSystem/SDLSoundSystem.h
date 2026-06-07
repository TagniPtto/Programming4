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

	class SDLSoundSystem : public ISoundSystem {
	private:
		MIX_Mixer* m_pMixer = NULL;
		MIX_Track* m_pTrack = NULL;

		std::thread m_worker;
		std::mutex m_mutex;
		std::condition_variable m_conditional_variable;
		std::unordered_map<std::string,MIX_Audio*> m_loadedAudio;
		std::queue<SoundEvent> m_eventQueue;


		std::atomic_bool threadIsRunning = true;
	private:
		void ThreadProcess();

	protected:
		friend class Minigin;
		SDLSoundSystem();

	public:
		virtual void LoadAudio(const std::string& path , const std::string& name) override;
		virtual void UnloadAudio(const std::string& name) override;
		virtual void Play(const std::string& name, const float volume)  override;

		virtual ~SDLSoundSystem();
	};
}