#pragma once
#include <memory>
#include "SoundSystem/ISoundSystem.h"


namespace dae {

	class ServiceLocator final
	{
		static std::unique_ptr<ISoundSystem> _ss_instance;
	public:
		static ISoundSystem& get_sound_system() { return *_ss_instance; }
		static void register_sound_system(std::unique_ptr<ISoundSystem>&& ss) { _ss_instance = std::move(ss); };

	};
}
