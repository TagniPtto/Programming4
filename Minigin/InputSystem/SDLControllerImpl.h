#pragma once 

#include "IGamepadImpl.h"

#include "SDL3/SDL.h"

namespace dae {
	class SDLControllerImpl final : public IGamepadImpl {

	private:
		unsigned int m_id;
	public:
		bool IsHeld(unsigned int button) const;
		bool IsReleasedThisFrame(unsigned int button) const;
		bool IsPressedThisFrame(unsigned int button) const;
		void ProcessInput();
		float GetLeftThumbX() const;
		float GetLeftThumbY() const;
		float GetRightThumbX() const;
		float GetRightThumbY() const;
		float GetLeftTrigger() const;
		float GetRightTrigger() const;

		unsigned int GetId() const;

		SDLControllerImpl(unsigned int id);
		~SDLControllerImpl() = default;


	};

}
