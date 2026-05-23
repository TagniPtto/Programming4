#pragma once
#include <memory>

namespace dae
{

	class ICommand;
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
	enum class TriggerType {
		Released,
		Pressed,
		Held,
	};
	struct InputBinding {
		unsigned int controllerId;

		unsigned int code;

		InputType type;
		InputValueType valueType;
 		TriggerType trigger;
	};

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
		void BindCommand(std::unique_ptr<ICommand> command,InputType inputType, unsigned int code, TriggerType triggerType , unsigned int id = 0);

	private:
		std::unique_ptr<InputManagerImpl> m_pImpl;
	};

}
