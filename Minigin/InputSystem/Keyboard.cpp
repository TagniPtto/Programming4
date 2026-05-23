#include "Keyboard.h"


#include "SDL3/SDL_keyboard.h"

dae::Keyboard::Keyboard() {

}
void dae::Keyboard::ProcessInput()
{
	const bool* kbState = SDL_GetKeyboardState(nullptr);
	m_previousState = m_currentState;
	memcpy(m_currentState.data(), kbState,SDL_SCANCODE_COUNT * sizeof(uint8_t));
}

bool dae::Keyboard::IsKeyHeldThisFrame(unsigned int code) const
{
	return m_currentState[code];
}

bool dae::Keyboard::IsKeyReleasedThisFrame(unsigned int code) const
{
	return !m_currentState[code] && m_previousState[code];
}	

bool dae::Keyboard::IsKeyPressedThisFrame(unsigned int code) const
{
	return m_currentState[code] && !m_previousState[code];
}
