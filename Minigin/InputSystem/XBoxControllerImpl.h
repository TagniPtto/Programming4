#pragma once

#ifdef _WIN32

#include "IGamepadImpl.h"

#include <windows.h> 
#include "Xinput.h"
#pragma comment(lib, "xinput.lib")



namespace dae {
	class XBoxControllerImpl final : public IGamepadImpl {

	private:

		XINPUT_STATE m_currentState;
		XINPUT_STATE m_previousState;

		WORD m_buttonsPressedThisFrame;
		WORD m_buttonsReleasedThisFrame;

		unsigned int m_id;
	public:
		bool IsHeld(unsigned int button) const;
		bool IsReleasedThisFrame(unsigned int button) const;
		bool IsPressedThisFrame(unsigned int button) const;
		void ProcessInput();
		float GetLeftThumbX() const { return m_currentState.Gamepad.sThumbLX; }
		float GetLeftThumbY() const { return m_currentState.Gamepad.sThumbLY; }
		float GetRightThumbX() const { return m_currentState.Gamepad.sThumbRX; }
		float GetRightThumbY() const { return m_currentState.Gamepad.sThumbRY; }
		float GetLeftTrigger() const { return m_currentState.Gamepad.bLeftTrigger; }
		float GetRightTrigger() const { return m_currentState.Gamepad.bRightTrigger; }

		unsigned int GetId() const;

		XBoxControllerImpl(unsigned int id);
		~XBoxControllerImpl() = default;


	};
}
#endif