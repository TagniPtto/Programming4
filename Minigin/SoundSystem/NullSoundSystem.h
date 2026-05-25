#pragma once 

#include "ISoundSystem.h"

namespace dae {
	class NullSoundSystem final : public ISoundSystem {
		virtual void UnloadAudio(const std::string& name) {};
		void LoadAudio(const std::string& fname, const std::string& name) override {};
		void Play(const std::string& name, const float volume) override {};
		~NullSoundSystem() override = default;
	};
}