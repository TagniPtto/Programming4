#pragma once
#include "Event.h"




namespace dae 
{


	struct SoundEvent : public Event {
		virtual ~SoundEvent() = default;
		SoundEvent(unsigned short i, float v)
			: id(i), volume(v)
		{
		}

		DEFINE_EVENT_CLASS_TYPE(sound_event);

		unsigned short id{};
		float volume{};
	};

}