#pragma once 

#include <array>
#include "SDL3/SDL_scancode.h"

namespace dae {
	class Keyboard final {
		friend class InputManager;

	private:
		std::array<uint8_t, SDL_SCANCODE_COUNT> m_currentState{};
		std::array<uint8_t, SDL_SCANCODE_COUNT> m_previousState{};
	private:
		Keyboard();

	public:
		void ProcessInput();
		bool IsKeyHeldThisFrame(unsigned int code) const;
		bool IsKeyReleasedThisFrame(unsigned int code) const;
		bool IsKeyPressedThisFrame(unsigned int code) const;

		~Keyboard() = default;
		Keyboard(const Keyboard&) = delete;
		Keyboard(Keyboard&&) = delete;
		Keyboard& operator=(const Keyboard&) = delete;
		Keyboard& operator=(Keyboard&&) = delete;
	};
}