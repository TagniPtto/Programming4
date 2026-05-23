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

		XBoxControllerImpl(unsigned int id);
		~XBoxControllerImpl() = default;


	};
}
#endif