
#include "SDL3/SDL_mouse.h"

#include "Mouse.h"



void dae::Mouse::ProcessInput()
{
	m_previousButtonState = m_currentButtonState;
	m_currentButtonState = SDL_GetMouseState(&m_x, &m_y);

	Uint32 buttonsChanged = m_previousButtonState ^ m_currentButtonState;
	m_buttonsReleasedThisFrame = m_previousButtonState & buttonsChanged;
	m_buttonsPressedThisFrame = buttonsChanged & m_currentButtonState;
}

bool dae::Mouse::IsButtonHeldThisFrame(unsigned int code) const
{
	return m_currentButtonState & code;
}

bool dae::Mouse::IsButtonReleasedThisFrame(unsigned int code) const
{
	return m_buttonsReleasedThisFrame & code;
}

bool dae::Mouse::IsButtonPressedThisFrame(unsigned int code) const
{
	return m_buttonsPressedThisFrame & code;
}

float dae::Mouse::GetMouseX() const
{
	return  m_x;
}

float dae::Mouse::GetMouseY() const
{
	return m_y;
}
