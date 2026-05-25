#pragma once 

#include "../IInputDevice.h"

#include "SDL3/SDL_scancode.h"

#include <array>
#include <unordered_map>

namespace dae {
	class Keyboard final : public IInputDevice{
		friend class InputManagerImpl;
	private:
		std::array<uint8_t, SDL_SCANCODE_COUNT> m_currentState{};
		std::array<uint8_t, SDL_SCANCODE_COUNT> m_previousState{};
	private:
		Keyboard();

	public:

		void ProcessInput() override;

		bool GetButtonHeld(uint32_t code) const override;
		bool GetButtonReleased(uint32_t code) const override;
		bool GetButtonPressed(uint32_t code) const override;

		float GetAxis1D(uint32_t code) const override;
		glm::vec2 GetAxis2D(uint32_t code) const override;

		~Keyboard() = default;
		Keyboard(const Keyboard&) = delete;
		Keyboard(Keyboard&&) = delete;
		Keyboard& operator=(const Keyboard&) = delete;
		Keyboard& operator=(Keyboard&&) = delete;
	};
}