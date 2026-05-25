#pragma once


#include "../IInputDevice.h"

namespace dae 
{
	class Mouse final : public IInputDevice
	{
		friend class InputManagerImpl;
	private:
		Mouse() = default;
		float m_x{};
		float m_y{};
		Uint32 m_currentButtonState{};
		Uint32 m_previousButtonState{};

		Uint32 m_buttonsPressedThisFrame{};
		Uint32 m_buttonsReleasedThisFrame{};
	public:

		void ProcessInput() override;
		bool GetButtonHeld(uint32_t code) const override;
		bool GetButtonPressed(uint32_t code) const override;
		bool GetButtonReleased(uint32_t code) const override;

		float GetAxis1D(uint32_t code) const override;
		glm::vec2 GetAxis2D(uint32_t code) const override;


		~Mouse() = default;
		Mouse(const Mouse&) = delete;
		Mouse(Mouse&&) = delete;
		Mouse& operator=(const Mouse&) = delete;
		Mouse& operator=(Mouse&&) = delete;
	};
}