#pragma once

#include "ISoundSystem.h"


#include <unordered_map>
#include <queue>
#include <thread>
#include <condition_variable>
#include <mutex>

struct MIX_Mixer;
struct MIX_Track;
struct MIX_Audio;

namespace dae
{
	class SDLSoundSystem : public ISoundSystem {
	private:
		MIX_Mixer* m_pMixer = nullptr;
		MIX_Track* m_pSfxTrack = nullptr;
		MIX_Track* m_pMusicTrack = nullptr;

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
		virtual ~SDLSoundSystem();
		SDLSoundSystem(const SDLSoundSystem&) = delete;
		SDLSoundSystem(SDLSoundSystem&&) = delete;
		SDLSoundSystem& operator=(const SDLSoundSystem&) = delete;
		SDLSoundSystem& operator=(SDLSoundSystem&&) = delete;


	public:
		virtual void LoadAudio(const std::string& path , const std::string& name) override;
		virtual void UnloadAudio(const std::string& name) override;
		virtual void PlayAudio(const std::string& name, const float volume)  override;
		virtual void PlayMusic(const std::string& name, const float volume)  override;


	};
}