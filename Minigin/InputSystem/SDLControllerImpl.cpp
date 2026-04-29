#include "SDLControllerImpl.h"



bool dae::SDLControllerImpl::IsHeld(unsigned int button) const
{
	return false;
}

bool dae::SDLControllerImpl::IsReleasedThisFrame(unsigned int button) const
{
	return false;
}

bool dae::SDLControllerImpl::IsPressedThisFrame(unsigned int button) const
{
	return false;
}

void dae::SDLControllerImpl::ProcessInput()
{
}

float dae::SDLControllerImpl::GetLeftThumbX() const
{
	return 0.0f;
}

float dae::SDLControllerImpl::GetLeftThumbY() const
{
	return 0.0f;
}

float dae::SDLControllerImpl::GetRightThumbX() const
{
	return 0.0f;
}

float dae::SDLControllerImpl::GetRightThumbY() const
{
	return 0.0f;
}

float dae::SDLControllerImpl::GetLeftTrigger() const
{
	return 0.0f;
}

float dae::SDLControllerImpl::GetRightTrigger() const
{
	return 0.0f;
}

unsigned int dae::SDLControllerImpl::GetId() const
{
	return 0;
}

dae::SDLControllerImpl::SDLControllerImpl(unsigned int id)
{
}
