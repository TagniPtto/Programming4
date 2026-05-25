#pragma once
#include "Event.h"

namespace dae 
{
	struct SoundEvent : public Event
	{
		DEFINE_EVENT_CLASS_TYPE(sound_event);

		SoundEvent(std::string n, float v)
			: name(std::move(n)), volume(v)
		{
		}

		virtual ~SoundEvent() = default;

		std::string name;
		float volume;
	};

}