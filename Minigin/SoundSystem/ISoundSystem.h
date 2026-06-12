#pragma once
#include <string>
#include "EventSystem/Events/SoundEvent.h"

namespace dae 
{
	class ISoundSystem 
	{
	protected:
		friend class Minigin;
		ISoundSystem() = default;

	public:
		virtual void LoadAudio(const std::string& fname, const std::string& name) = 0;
		virtual void UnloadAudio(const std::string& name) = 0;
		virtual void PlayAudio(const std::string& name, const float volume) = 0;
		virtual void PlayMusic(const std::string& name, const float volume) = 0;

		virtual ~ISoundSystem() = default;
	};
}