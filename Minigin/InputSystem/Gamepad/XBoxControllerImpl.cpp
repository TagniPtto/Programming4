
#ifdef _WIN32

#include "XBoxControllerImpl.h"

#include "cmath"


	bool dae::XBoxControllerImpl::IsButtonHeld(uint32_t code) const
	{
		return m_currentState.Gamepad.wButtons & code;
	}

	bool dae::XBoxControllerImpl::IsButtonReleased(uint32_t code)const
	{
		return m_buttonsReleasedThisFrame & code;
	}

	bool dae::XBoxControllerImpl::IsButtonPressed(uint32_t code)const
	{
		return m_buttonsPressedThisFrame & code;
	}

	void dae::XBoxControllerImpl::ProcessInput()
	{
		CopyMemory(&m_previousState, &m_currentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_currentState, sizeof(XINPUT_STATE));
		XInputGetState(m_id, &m_currentState);

		//adjust for deadzones

		m_currentState.Gamepad.sThumbLX = (std::abs(m_currentState.Gamepad.sThumbLX) < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ? 0 : m_currentState.Gamepad.sThumbLX;
		m_currentState.Gamepad.sThumbLY = (std::abs(m_currentState.Gamepad.sThumbLY) < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ? 0 : m_currentState.Gamepad.sThumbLY;
		m_currentState.Gamepad.sThumbRX = (std::abs(m_currentState.Gamepad.sThumbRX) < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ? 0 : m_currentState.Gamepad.sThumbRX;
		m_currentState.Gamepad.sThumbRY = (std::abs(m_currentState.Gamepad.sThumbRY) < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ? 0 : m_currentState.Gamepad.sThumbRY;



		auto buttonsChanged = m_previousState.Gamepad.wButtons ^ m_currentState.Gamepad.wButtons; // ^ is xor operation

		m_buttonsPressedThisFrame = buttonsChanged & m_currentState.Gamepad.wButtons;
		m_buttonsReleasedThisFrame = buttonsChanged & m_previousState.Gamepad.wButtons;
	}

	float dae::XBoxControllerImpl::GetLeftThumbX() const
	{
		return m_currentState.Gamepad.sThumbLX; 
	}
	float dae::XBoxControllerImpl::GetLeftThumbY() const 
	{
		return m_currentState.Gamepad.sThumbLY;
	}
	float dae::XBoxControllerImpl::GetRightThumbX() const
	{
		return m_currentState.Gamepad.sThumbRY;
	}

	float dae::XBoxControllerImpl::GetRightThumbY() const
	{ 
		return m_currentState.Gamepad.sThumbRY;
	}

	float dae::XBoxControllerImpl::GetLeftTrigger() const
	{
		return m_currentState.Gamepad.bLeftTrigger;
	}

	float dae::XBoxControllerImpl::GetRightTrigger() const
	{
		return m_currentState.Gamepad.bRightTrigger;
	}

	unsigned int dae::XBoxControllerImpl::GetId() const
	{
		return m_id;
	}

	dae::XBoxControllerImpl::XBoxControllerImpl(unsigned int id) :
		m_id(id), m_buttonsPressedThisFrame(0), m_buttonsReleasedThisFrame(0), m_currentState(), m_previousState()
	{
	}


#endif