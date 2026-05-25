#pragma once
#include <memory>
#include <cstdint>
#include "InputTypes.h"

namespace dae
{
	enum class InputType
	{
		Keyboard,
		Mouse,
		Gamepad
	};
	enum class InputValueType
	{
		Boolean,
		Float,
		Vector2,
	};
	enum class InputTriggerType {
		Released,
		Pressed,
		Held,
	};
	struct InputBinding {
		uint32_t code;

		uint32_t deviceIndex;
		InputType deviceType;

		InputValueType deviceValue;
 		InputTriggerType trigger;
	};


	class ICommand;
	class InputManagerImpl;
	class InputManager final
	{
	private:
		InputManager();
		~InputManager();

	public:
		static InputManager& GetInstance() {
			static InputManager instance{};
			return instance;
		}
		InputManager(const InputManager& other) = delete;
		InputManager(InputManager&& other) = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager& operator=(InputManager&& other) = delete;

		bool ProcessInput();

		void BindCommand(std::unique_ptr<ICommand> command,InputBinding binding);
		void BindCommand(std::unique_ptr<ICommand> command, InputType inputType, uint32_t deviceId, InputValueType valueType, uint32_t code, InputTriggerType triggerType);
		
		void BindCommand(std::unique_ptr<ICommand> command, uint32_t deviceId,	InputValueType valueType, GamepadInput code, InputTriggerType triggerType);
		void BindCommand(std::unique_ptr<ICommand> command,						InputValueType valueType, KeyboardInput code, InputTriggerType triggerType);
		void BindCommand(std::unique_ptr<ICommand> command,						InputValueType valueType, MouseInput code, InputTriggerType triggerType);

	private:
		std::unique_ptr<InputManagerImpl> m_pImpl;
	};

}
