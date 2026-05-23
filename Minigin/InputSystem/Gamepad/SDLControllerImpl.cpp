#include "SDLControllerImpl.h"

#include <limits>



bool dae::SDLControllerImpl::IsHeld(unsigned int button) const
{
	return m_currentButtonState[button];
}

bool dae::SDLControllerImpl::IsReleasedThisFrame(unsigned int button) const
{
	return !m_currentButtonState[button] && m_previousButtonState[button];
}

bool dae::SDLControllerImpl::IsPressedThisFrame(unsigned int button) const
{
	return m_currentButtonState[button] && !m_previousButtonState[button];;
}

void dae::SDLControllerImpl::ProcessInput()
{
	constexpr static float AXIS_MAX = static_cast<float>(std::numeric_limits<Sint16>::max());
	m_previousButtonState = m_currentButtonState;

	for (int i{}; i < SDL_GAMEPAD_BUTTON_COUNT; ++i)
	{
		m_currentButtonState[i] = SDL_GetGamepadButton(m_gamepad,static_cast<SDL_GamepadButton>(i));
	}

	leftThumbX	= SDL_GetGamepadAxis(m_gamepad,SDL_GAMEPAD_AXIS_LEFTX) / AXIS_MAX;
	leftThumbY	= SDL_GetGamepadAxis(m_gamepad,SDL_GAMEPAD_AXIS_LEFTY) / AXIS_MAX;
	
	rightThumbX	= SDL_GetGamepadAxis(m_gamepad,SDL_GAMEPAD_AXIS_RIGHTX) / AXIS_MAX;
	rightThumbY	= SDL_GetGamepadAxis(m_gamepad,SDL_GAMEPAD_AXIS_RIGHTY)	/ AXIS_MAX;
	
	leftTrigger	= SDL_GetGamepadAxis(m_gamepad,SDL_GAMEPAD_AXIS_LEFT_TRIGGER)	/ AXIS_MAX;
	rightTrigger = SDL_GetGamepadAxis(m_gamepad,SDL_GAMEPAD_AXIS_RIGHT_TRIGGER)	/ AXIS_MAX;

}

float dae::SDLControllerImpl::GetLeftThumbX() const
{
	return leftThumbX;
}

float dae::SDLControllerImpl::GetLeftThumbY() const
{
	return leftThumbY;
}

float dae::SDLControllerImpl::GetRightThumbX() const
{
	return rightThumbX;
}

float dae::SDLControllerImpl::GetRightThumbY() const
{
	return rightThumbY;
}

float dae::SDLControllerImpl::GetLeftTrigger() const
{
	return leftTrigger;
}

float dae::SDLControllerImpl::GetRightTrigger() const
{
	return rightTrigger;
}

unsigned int dae::SDLControllerImpl::GetId() const
{
	return m_id;
}

dae::SDLControllerImpl::SDLControllerImpl(unsigned int id):
	m_id(id)
{
	if (SDL_IsGamepad(id))
	{
		m_gamepad = SDL_OpenGamepad(id);

		if (m_gamepad)
		{
			SDL_Log("Opened Gamepad: %s",
				SDL_GetGamepadName(m_gamepad));
		}
		else
		{
			SDL_Log("Failed to open gamepad: %s",
				SDL_GetError());
		}
	}
}
