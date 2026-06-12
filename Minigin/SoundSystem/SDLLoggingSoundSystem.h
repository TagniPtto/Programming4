#pragma once

#include "SDLSoundSystem.h"
namespace dae {
	class SDLLoggingSoundSystem final: public SDLSoundSystem {
	private:
		friend class Minigin;
		SDLLoggingSoundSystem() = default;
	public:
		void LoadAudio(const std::string& path, const std::string& name) override;
		void UnloadAudio(const std::string& name) override;
		void PlayAudio(const std::string& name, const float volume)  override;
		void PlayMusic(const std::string& name, const float volume) override;

	};
}