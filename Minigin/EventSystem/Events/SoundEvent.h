#pragma once
#include "Event.h"


namespace dae 
{
	enum class AudioType {
		SFX,
		Music
	};
	struct SoundEvent : public Event
	{

		DEFINE_EVENT_CLASS_TYPE(sound_event);

		virtual ~SoundEvent() = default;
		SoundEvent(std::string n,float v , AudioType t = AudioType::SFX):
			name(n),
			volume(v),
			type(t)
		{
		}


		AudioType type;
		std::string name;
		float volume;
	};

}