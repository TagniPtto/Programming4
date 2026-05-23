#pragma once
#include <string>
#include "EventSystem/Events/SoundEvent.h"

namespace dae 
{

	using sound_id = unsigned short;

	class ISoundSystem 
	{
	public:
		virtual void LoadAudio(std::string fname) = 0;
		virtual void UnloadAudio(const sound_id id) = 0;
		virtual void Play(const sound_id id, const float volume) = 0;

		ISoundSystem() = default;
		virtual ~ISoundSystem() = default;

		ISoundSystem(const ISoundSystem& other) = delete;
		ISoundSystem(ISoundSystem&& other) = delete;

		ISoundSystem& operator=(const ISoundSystem& other) = delete;
		ISoundSystem& operator=(ISoundSystem&& other) = delete;

	};
}