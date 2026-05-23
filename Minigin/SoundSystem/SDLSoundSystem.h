#pragma once

#include "ISoundSystem.h"


#include <vector>
#include <queue>
#include <thread>
#include <condition_variable>
#include <mutex>

#include <SDL3_mixer/SDL_mixer.h>

namespace dae
{
	using sound_id = unsigned short;

	class SDLSoundSystem final : public ISoundSystem {
	private:
		MIX_Mixer* m_pMixer = NULL;
		MIX_Track* m_pTrack = NULL;

		std::jthread m_worker;
		std::mutex m_mutex;
		std::condition_variable m_conditional_variable;
		std::vector<MIX_Audio*> m_loadedAudio;
		std::queue<SoundEvent> m_eventQueue;


		std::atomic_bool threadIsRunning = true;
	public:
		void Update();
		void ThreadProcess();
		void LoadAudio(std::string path) override;
		void UnloadAudio(const sound_id id) override;
		void Play(const sound_id id, const float volume)  override;
		SDLSoundSystem();
		~SDLSoundSystem() override;
	};
}