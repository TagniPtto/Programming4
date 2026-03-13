#pragma once

#define WIN32_LEAN_AND_MEAN 
#include <windows.h> 
#include "Xinput.h"

#pragma comment(lib, "xinput.lib")


namespace dae {

	class Gamepad final {

	private:
		XINPUT_STATE m_currentState;
		XINPUT_STATE m_previousState;
	
		WORD m_buttonsPressedThisFrame;
		WORD m_buttonsReleasedThisFrame;
	
		unsigned int m_id;
	public:
		bool IsPressed(unsigned int button) const;
		bool IsReleasedThisFrame(unsigned int button) const;
		bool IsPressedThisFrame(unsigned int button) const;
		void ProcessInput();

		Gamepad(unsigned int id);

		~Gamepad() = default;
		Gamepad(const Gamepad& gp) = delete;
		Gamepad(Gamepad&& gp) = delete;
		Gamepad& operator=(const Gamepad& gp) = delete;
		Gamepad& operator=(Gamepad&& gp) = delete;

	};
}