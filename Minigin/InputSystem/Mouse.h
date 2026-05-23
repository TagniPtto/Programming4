#pragma once


namespace dae 
{
	class Mouse final
	{
		friend class InputManager;
	private:
		Mouse() = default;
		float m_x{};
		float m_y{};
		Uint32 m_currentButtonState{};
		Uint32 m_previousButtonState{};

		Uint32 m_buttonsPressedThisFrame{};
		Uint32 m_buttonsReleasedThisFrame{};
	public:

		void ProcessInput();
		bool IsButtonHeldThisFrame(unsigned int code) const;
		bool IsButtonReleasedThisFrame(unsigned int code) const;
		bool IsButtonPressedThisFrame(unsigned int code) const;
		float GetMouseX() const;
		float GetMouseY() const;
		~Mouse() = default;
		Mouse(const Mouse&) = delete;
		Mouse(Mouse&&) = delete;
		Mouse& operator=(const Mouse&) = delete;
		Mouse& operator=(Mouse&&) = delete;
	};
}