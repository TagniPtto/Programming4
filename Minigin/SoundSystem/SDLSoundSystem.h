#pragma once

#include "ISoundSystem.h"
#include <vector>

#include <SDL3_mixer/SDL_mixer.h>

namespace dae
{
	class SDLSoundSystem final : public ISoundSystem {
	private:
		MIX_Mixer* m_pMixer = NULL;
		MIX_Track* m_pTrack = NULL;

		std::vector<MIX_Audio*> loadedAudio;
	public:
		
		void LoadAudio(std::string path) override;
		void play(const sound_id id, const float volume)  override;
		SDLSoundSystem();
		~SDLSoundSystem() override;
	};
}