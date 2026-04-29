#include "Gamepad.h"
#include "XBoxControllerImpl.h"
#include "SDLControllerImpl.h"

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

bool dae::Gamepad::IsHeld(unsigned int button) const
{
	return m_pImpl->IsHeld(button);
}
bool dae::Gamepad::IsReleasedThisFrame(unsigned int button) const
{
	return m_pImpl->IsReleasedThisFrame(button);
}
bool dae::Gamepad::IsPressedThisFrame(unsigned int button) const
{
	return m_pImpl->IsPressedThisFrame(button);
}
float dae::Gamepad::GetLeftThumbX() const
{
	return m_pImpl->GetLeftThumbX();
}
float dae::Gamepad::GetLeftThumbY() const
{
	return m_pImpl->GetLeftThumbY();
}
float dae::Gamepad::GetRightThumbX() const
{
	return m_pImpl->GetRightThumbX();
}
float dae::Gamepad::GetRightThumbY() const
{
	return m_pImpl->GetRightThumbY();
}
float dae::Gamepad::GetLeftTrigger() const
{
	return m_pImpl->GetLeftTrigger();
}
float dae::Gamepad::GetRightTrigger() const
{
	return m_pImpl->GetRightTrigger();
}
unsigned int dae::Gamepad::GetId() const
{
	return m_pImpl->GetId();
}
void dae::Gamepad::ProcessInput()
{
	return m_pImpl->ProcessInput();
}



