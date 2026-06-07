#pragma once 

#include "ISoundSystem.h"

namespace dae {
	class NullSoundSystem final : public ISoundSystem {
	protected:
		friend class Minigin;
		NullSoundSystem() = default;
	public:
		virtual void UnloadAudio(const std::string&) {};
		void LoadAudio(const std::string&, const std::string&) override {};
		void Play(const std::string&, const float) override {};

		~NullSoundSystem() = default;
	};
}