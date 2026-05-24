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
		XBoxControllerImpl(unsigned int id);
		~XBoxControllerImpl() = default;
		
		void ProcessInput() override;
		unsigned int GetId() const override;

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
#endif