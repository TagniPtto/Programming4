#pragma once 

#include "ISoundSystem.h"

namespace dae {
	class NullSoundSystem final : public ISoundSystem {
		void LoadAudio(std::string fname) override {};
		void play(const sound_id id, const float volume) override {};
	};
}