#pragma once 

#include "ISoundSystem.h"

namespace dae {
	class NullSoundSystem final : public ISoundSystem {
	protected:
		friend class Minigin;
		NullSoundSystem() = default;
	public:
		void UnloadAudio(const std::string&) {};
		void LoadAudio(const std::string&, const std::string&) override {};
		void PlayAudio(const std::string&, const float) override {};
		void StreamMusic(const std::string& name, const float volume) {};

		~NullSoundSystem() = default;
	};
}