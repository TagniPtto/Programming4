#include "Gamepad.h"


#define WIN32_LEAN_AND_MEAN 
#include <windows.h> 
#include "Xinput.h"

#pragma comment(lib, "xinput.lib")


namespace dae {

	class GamepadImpl final {

	private:
		XINPUT_STATE m_currentState;
		XINPUT_STATE m_previousState;

		WORD m_buttonsPressedThisFrame;
		WORD m_buttonsReleasedThisFrame;

		unsigned int m_id;
	public:
		bool IsHeld(unsigned int button) const;
		bool IsReleasedThisFrame(unsigned int button) const;
		bool IsPressedThisFrame(unsigned int button) const;
		void ProcessInput();
		float GetLeftThumbX() const { return m_currentState.Gamepad.sThumbLX; }
		float GetLeftThumbY() const { return m_currentState.Gamepad.sThumbLY; }
		float GetRightThumbX() const { return m_currentState.Gamepad.sThumbRX; }
		float GetRightThumbY() const { return m_currentState.Gamepad.sThumbRY; }
		float GetLeftTrigger() const { return m_currentState.Gamepad.bLeftTrigger; }
		float GetRightTrigger() const { return m_currentState.Gamepad.bRightTrigger; }

		unsigned int GetId() const;

		GamepadImpl(unsigned int id);

		~GamepadImpl() = default;
		GamepadImpl(const GamepadImpl& gp) = delete;
		GamepadImpl(GamepadImpl&& gp) = delete;
		GamepadImpl& operator=(const GamepadImpl& gp) = delete;
		GamepadImpl& operator=(GamepadImpl&& gp) = delete;

	};


	bool GamepadImpl::IsHeld(unsigned int button) const
	{
		return m_currentState.Gamepad.wButtons & button;
	}

	bool GamepadImpl::IsReleasedThisFrame(unsigned int button)const
	{
		return m_buttonsReleasedThisFrame & button;
	}

	bool GamepadImpl::IsPressedThisFrame(unsigned int button)const
	{
		return m_buttonsPressedThisFrame & button;
	}

	void GamepadImpl::ProcessInput()
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

	unsigned int GamepadImpl::GetId() const
	{
		return m_id;
	}

	GamepadImpl::GamepadImpl(unsigned int id):
		m_id(id), m_buttonsPressedThisFrame(0), m_buttonsReleasedThisFrame(0), m_currentState(), m_previousState()
	{
	}

}


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
void dae::Gamepad::ProcessInput()
{
	return m_pImpl->ProcessInput();
}
unsigned int dae::Gamepad::GetId() const
{
	return m_pImpl->GetId();
}

dae::Gamepad::Gamepad(unsigned int id):
	m_pImpl(std::make_unique<GamepadImpl>(id))
{
}

dae::Gamepad::~Gamepad() = default;

