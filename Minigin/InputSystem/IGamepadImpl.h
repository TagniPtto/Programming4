#pragma once
namespace dae {
	class IGamepadImpl {
	public:
		virtual bool IsHeld(unsigned int button) const = 0;
		virtual bool IsReleasedThisFrame(unsigned int button) const = 0;
		virtual bool IsPressedThisFrame(unsigned int button) const = 0;

		virtual float GetLeftThumbX() const = 0;
		virtual float GetLeftThumbY() const = 0;
		virtual float GetRightThumbX() const = 0;
		virtual float GetRightThumbY() const = 0;
		virtual float GetLeftTrigger() const = 0;
		virtual float GetRightTrigger() const = 0;

		virtual void ProcessInput() = 0;
		virtual unsigned int GetId() const = 0;

		IGamepadImpl() = default;
		virtual ~IGamepadImpl() = default;
		IGamepadImpl(const IGamepadImpl& gp) = delete;
		IGamepadImpl(IGamepadImpl&& gp) = delete;
		IGamepadImpl& operator=(const IGamepadImpl& gp) = delete;
		IGamepadImpl& operator=(IGamepadImpl&& gp) = delete;
	};
}
