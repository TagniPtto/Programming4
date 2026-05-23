#pragma once 

#include "IGamepadImpl.h"

#include "SDL3/SDL.h"
#include <array>

namespace dae {
	class SDLControllerImpl final : public IGamepadImpl {

	private:
		unsigned int m_id;
		SDL_Gamepad* m_gamepad{};

		std::array<bool, SDL_GAMEPAD_BUTTON_COUNT> m_previousButtonState{};
		std::array<bool, SDL_GAMEPAD_BUTTON_COUNT> m_currentButtonState{};


		float leftThumbX{};
		float leftThumbY{};

		float rightThumbX{};
		float rightThumbY{};

		float leftTrigger{};
		float rightTrigger{};

	public:
		void ProcessInput();

		bool IsHeld(unsigned int button) const;
		bool IsReleasedThisFrame(unsigned int button) const;
		bool IsPressedThisFrame(unsigned int button) const;
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
