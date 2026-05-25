#include "SDLControllerImpl.h"

#include <limits>

#include "../InputTypes.h"


SDL_GamepadButton ToSDLButton(dae::GamepadInput input);


bool dae::SDLControllerImpl::IsButtonHeld(uint32_t code) const
{
	return m_currentButtonState[ToSDLButton(GamepadInput(code))];
}

bool dae::SDLControllerImpl::IsButtonReleased(uint32_t code) const
{
	return !m_currentButtonState[ToSDLButton(GamepadInput(code))] && m_previousButtonState[ToSDLButton(GamepadInput(code))];
}

bool dae::SDLControllerImpl::IsButtonPressed(uint32_t code) const
{
	return m_currentButtonState[ToSDLButton(GamepadInput(code))] && !m_previousButtonState[ToSDLButton(GamepadInput(code))];;
}

void dae::SDLControllerImpl::ProcessInput()
{

	m_previousButtonState = m_currentButtonState;

	for (int i{}; i < SDL_GAMEPAD_BUTTON_COUNT; ++i)
	{
		m_currentButtonState[i] = SDL_GetGamepadButton(m_gamepad,static_cast<SDL_GamepadButton>(i));
	}

	constexpr static float AXIS_MAX = static_cast<float>(std::numeric_limits<Sint16>::max());

	
	
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
			SDL_Log("Opened Gamepad: %s",SDL_GetGamepadName(m_gamepad));
		}
		else
		{
			SDL_Log("Failed to open gamepad: %s",SDL_GetError());
		}
	}
}
SDL_GamepadButton ToSDLButton(dae::GamepadInput input)
{
	switch (input)
	{
	case dae::GamepadInput::ButtonA:			return SDL_GAMEPAD_BUTTON_SOUTH;
	case dae::GamepadInput::ButtonB:			return SDL_GAMEPAD_BUTTON_EAST;
	case dae::GamepadInput::ButtonX:			return SDL_GAMEPAD_BUTTON_WEST;
	case dae::GamepadInput::ButtonY:			return SDL_GAMEPAD_BUTTON_NORTH;
	case dae::GamepadInput::LeftShoulder:		return SDL_GAMEPAD_BUTTON_LEFT_SHOULDER;
	case dae::GamepadInput::RightShoulder:		return SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER;
	case dae::GamepadInput::Start:				return SDL_GAMEPAD_BUTTON_START;
	case dae::GamepadInput::Back:				return SDL_GAMEPAD_BUTTON_BACK;
	case dae::GamepadInput::LeftThumb:			return SDL_GAMEPAD_BUTTON_LEFT_STICK;
	case dae::GamepadInput::RightThumb:			return SDL_GAMEPAD_BUTTON_RIGHT_STICK;
	case dae::GamepadInput::DPadUp:				return SDL_GAMEPAD_BUTTON_DPAD_UP;
	case dae::GamepadInput::DPadDown:			return SDL_GAMEPAD_BUTTON_DPAD_DOWN;
	case dae::GamepadInput::DPadLeft:			return SDL_GAMEPAD_BUTTON_DPAD_LEFT;
	case dae::GamepadInput::DPadRight:			return SDL_GAMEPAD_BUTTON_DPAD_RIGHT;
	default:									return SDL_GAMEPAD_BUTTON_INVALID;
	}
}