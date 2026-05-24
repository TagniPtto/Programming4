#include "Gamepad.h"

#include "IGamepadImpl.h"
#include "XBoxControllerImpl.h"
#include "SDLControllerImpl.h"

#include "InputTypes.h"

#ifdef WIN32
dae::Gamepad::Gamepad(unsigned int id) :
	m_pImpl(std::make_unique<XBoxControllerImpl>(id))
{
}
#else
dae::Gamepad::Gamepad(unsigned int id) :
	m_pImpl(std::make_unique<SDLControllerImpl>(id))
{
}
#endif
dae::Gamepad::~Gamepad() = default;

unsigned int dae::Gamepad::GetId()
{
	return m_pImpl->GetId();
}
void dae::Gamepad::ProcessInput()
{
	return m_pImpl->ProcessInput();
}

bool dae::Gamepad::GetButtonHeld(uint32_t code) const
{
	return m_pImpl->GetButtonHeld(button);
}

bool dae::Gamepad::GetButtonReleased(uint32_t code) const
{
	return m_pImpl->GetButtonReleased(button);
}

bool dae::Gamepad::GetButtonPressed(uint32_t code) const
{
	return m_pImpl->GetButtonPressed(button);
}

float dae::Gamepad::GetAxis1D(uint32_t code) const
{
	switch (code) {
		case GamepadInput::LeftTrigger:
			return m_pImpl->GetLeftTrigger();
		case GamepadInput::RightTrigger:
			return m_pImpl->GetRightTrigger();
	}
	return 0;
}

glm::vec2 dae::Gamepad::GetAxis2D(uint32_t code) const
{
	switch (code) {
	case GamepadInput::LeftThumb:
		return glm::vec2{ m_pImpl->GetLeftThumbX(),m_pImpl->GetLeftThumbY() };
	case GamepadInput::RightThumb:
		return glm::vec2{ m_pImpl->GetRightThumbX(),m_pImpl->GetRightThumbY() };
	}
	return glm::vec2{};
}






