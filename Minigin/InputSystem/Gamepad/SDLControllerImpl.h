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
		SDLControllerImpl(unsigned int id);
		~SDLControllerImpl() = default;

		unsigned int GetId() const override;
		void ProcessInput() override;

		bool IsButtonHeld(uint32_t code) const override;
		bool IsButtonReleased(uint32_t code) const override;
		bool IsButtonPressed(uint32_t code) const override;
		float GetLeftThumbX() const	override;
		float GetLeftThumbY() const	override;
		float GetRightThumbX() const override;
		float GetRightThumbY() const override;
		float GetLeftTrigger() const override;
		float GetRightTrigger() const override;
	};

}
