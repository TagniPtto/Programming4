#include "Gamepad.h"

dae::Gamepad::Gamepad(unsigned int id):
	m_id(id)
{

}
bool dae::Gamepad::IsPressed(unsigned int button) const
{
	return m_currentState.Gamepad.wButtons & button;
}

bool dae::Gamepad::IsReleasedThisFrame(unsigned int button)const
{
	return m_buttonsReleasedThisFrame & button;
}

bool dae::Gamepad::IsPressedThisFrame(unsigned int button)const
{
	return m_buttonsPressedThisFrame & button;
}

void dae::Gamepad::ProcessInput()
{
	CopyMemory(&m_previousState, &m_currentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_currentState, sizeof(XINPUT_STATE));
	XInputGetState(m_id, &m_currentState);

	auto buttonsChanged = m_previousState.Gamepad.wButtons ^ m_currentState.Gamepad.wButtons; // ^ is xor operation

	m_buttonsPressedThisFrame = buttonsChanged & m_currentState.Gamepad.wButtons;
	m_buttonsReleasedThisFrame = buttonsChanged & m_previousState.Gamepad.wButtons;
}



