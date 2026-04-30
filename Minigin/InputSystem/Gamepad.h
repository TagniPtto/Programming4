#pragma once

#include <memory>

namespace dae {
	enum class GamepadInputType {
		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000,
		LeftShoulder = 0x0100,
		RightShoulder = 0x0200,
		Start = 0x0010,
		Back = 0x0020,
		LeftThumb = 0x0040,
		RightThumb = 0x0080,
		DPadUp = 0x0001,
		DPadDown = 0x0002,
		DPadLeft = 0x0004,
		DPadRight = 0x0008
	};
	class IGamepadImpl;
	class Gamepad{
	private:
		std::unique_ptr<IGamepadImpl> m_pImpl;
	public:
		bool IsHeld(unsigned int button) const;
		bool IsReleasedThisFrame(unsigned int button) const;
		bool IsPressedThisFrame(unsigned int button) const;
	
		float GetLeftThumbX() const;
		float GetLeftThumbY() const;
		float GetRightThumbX() const;
		float GetRightThumbY() const;
		float GetLeftTrigger() const;
		float GetRightTrigger() const;

		void ProcessInput();
		unsigned int GetId() const;

		Gamepad(unsigned int id);
		~Gamepad();
		//Dont add = default with (unique ptr to a forwarded class) tries to delete but doesnt know what it actually is
		// 
		// 
		// Because that line is in the header, every .cpp that includes it generates:
		//	~Gamepad() {
		//	m_pImpl.~unique_ptr();
		//	}
		//delete IGamepadImpl*;


		Gamepad(const Gamepad& gp) = delete;
		Gamepad(Gamepad&& gp) = delete;
		Gamepad& operator=(const Gamepad& gp) = delete;
		Gamepad& operator=(Gamepad&& gp) = delete;

	};
}