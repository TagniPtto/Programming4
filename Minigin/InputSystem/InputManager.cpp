
#include "InputManager.h"


#include <glm/vec3.hpp>
#include <SDL3/SDL.h>
#include <backends/imgui_impl_sdl3.h>

#include <vector>


#include "Gamepad/Gamepad.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Commands.h"



#define MAX_CONTROLLERS 4
namespace dae {

	class InputManagerImpl final {

	private:
		std::vector<std::unique_ptr<Gamepad>> m_gamepads;
		std::vector< std::pair<InputBinding, std::unique_ptr<ICommand>>> m_bindings;

		std::unique_ptr<Mouse> m_mouse;
		std::unique_ptr<Keyboard> m_keyboard;


		std::unordered_map<int, TriggerType> m_triggerMappings{
			{SDL_EVENT_KEY_DOWN,			TriggerType::Pressed},
			{SDL_EVENT_KEY_UP,				TriggerType::Released},
			{SDL_EVENT_MOUSE_BUTTON_DOWN,	TriggerType::Pressed},
			{SDL_EVENT_MOUSE_BUTTON_UP,		TriggerType::Released},
			{SDL_EVENT_GAMEPAD_BUTTON_UP,	TriggerType::Released},
			{SDL_EVENT_GAMEPAD_BUTTON_DOWN,	TriggerType::Pressed},
		};

	public:
		InputManagerImpl();

		void BindCommand(std::unique_ptr<ICommand>  command, InputBinding binding);
		void BindCommand(std::unique_ptr<ICommand>  command, InputType inputType, unsigned int code, TriggerType triggerType, unsigned int id);
		bool ProcessInput();
	private:
		void ProcessGamepadBinding	(const InputBinding& binding, ICommand* command);
		void ProcessKeyboardBinding	(const InputBinding& binding, ICommand* command);
		void ProcessMouseBinding	(const InputBinding& binding, ICommand* command);
		void ProcessBindings();
	};




	InputManagerImpl::InputManagerImpl():
		m_mouse(std::make_unique<Mouse>()),
		m_keyboard(std::make_unique<Keyboard>())
	{
		for (unsigned int i = 0; i < MAX_CONTROLLERS; ++i)
		{
			m_gamepads.emplace_back(std::make_unique<dae::Gamepad>(i));
		}
	}


	void InputManagerImpl::BindCommand(std::unique_ptr<ICommand>  command, InputBinding binding)
	{
		m_bindings.emplace_back(binding, command);
	}

	void InputManagerImpl::BindCommand(std::unique_ptr<ICommand>  command, InputType inputType, unsigned int code, TriggerType triggerType, unsigned int id)
	{
		InputBinding binding{ .controllerId = id,.type = inputType, .trigger = triggerType ,.code = code};
		BindCommand(std::move(command), binding);
	}
	void InputManagerImpl::ProcessGamepadBinding(const InputBinding& binding, ICommand* command)
	{
		if (!(binding.controllerId < m_gamepads.size())) {
			return;
		}
		auto& gamepad = m_gamepads[binding.controllerId];
		if (binding.valueType == InputValueType::Boolean) {
			if ((binding.trigger == TriggerType::Held		&&	gamepad->IsHeld(binding.code))||
				(binding.trigger == TriggerType::Released	&&	gamepad->IsReleasedThisFrame(binding.code))||
				(binding.trigger == TriggerType::Pressed	&&	gamepad->IsPressedThisFrame(binding.code)))
			{
				command->Execute(glm::vec2(1.0f, 0.f));
			}
		}
		if (binding.valueType == InputValueType::Float) {
			float value = 0.f;

			if (binding.code == unsigned int(GamepadInputType::LeftShoulder)) {
				value = gamepad->GetLeftTrigger();

				if (value > 0.f) {
					command->Execute(glm::vec2(value, 0.f));
				}
			}

			if (binding.code == unsigned int(GamepadInputType::RightShoulder)) {
				value = gamepad->GetRightTrigger();

				if (value > 0.f) {
					command->Execute(glm::vec2(value, 0.f));
				}
			}

		}
		if (binding.valueType == InputValueType::Vector2) {


			if (binding.code == unsigned int(GamepadInputType::LeftThumb)) {
				float x = gamepad->GetLeftThumbX();
				float y = -gamepad->GetLeftThumbY();
				if (x || y) {
					command->Execute(glm::vec2(x, y));
				}
			}
			if(binding.code == unsigned int(GamepadInputType::RightThumb)) {
				
				float x = gamepad->GetRightThumbX();
				float y = -gamepad->GetRightThumbY();
				if (x || y) {
					command->Execute(glm::vec2(x, y));
				}
			}

		}
	}

	void InputManagerImpl::ProcessKeyboardBinding(const InputBinding& binding, ICommand* command)
	{
		if (m_triggerMappings.contains(e.type) &&
			m_triggerMappings[e.type] == binding.trigger &&
			unsigned int(e.key.scancode) == binding.code)
		{
			command->Execute(glm::vec2(1.0f, 0.f));
		}
		if (binding.type == InputType::Keyboard &&
			binding.trigger == TriggerType::Held)
		{
			command->Execute(glm::vec2(1.0f, 0.f));
		}
	}							

	void InputManagerImpl::ProcessMouseBinding(const InputBinding& binding, ICommand* command)
	{
		if (binding.trigger == TriggerType::Held) {

			float x, y;
			auto buttons = SDL_GetMouseState(&x, &y);
			if (buttons & SDL_BUTTON_MASK(binding.code)) {
				command->Execute(glm::vec2(x, y));
			}
		}
	}								

	void InputManagerImpl::ProcessBindings()
	{

		for (auto& [binding, command] : m_bindings) {
			switch (binding.type)
			{
			case InputType::Keyboard:
				ProcessKeyboardBinding(binding, command.get());
				break;
			case InputType::Gamepad:
				ProcessGamepadBinding(binding, command.get());
				break;
			case InputType::Mouse:
				ProcessMouseBinding(binding, command.get());
				break;
			}
		}
	}

	bool InputManagerImpl::ProcessInput()
	{

		for (auto& gamepad : m_gamepads) {
			gamepad->ProcessInput();
		}


		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_QUIT) {
				return false;
			}
			ImGui_ImplSDL3_ProcessEvent(&e);
		}


		ProcessBindings();
		return true;
	}
}











dae::InputManager::InputManager():
	m_pImpl(std::make_unique<dae::InputManagerImpl>())
{
}

bool dae::InputManager::ProcessInput()
{
	return m_pImpl->ProcessInput();
}

void dae::InputManager::BindCommand(std::unique_ptr<ICommand> command,InputBinding binding)
{
	return m_pImpl->BindCommand(std::move(command), binding);
}

void dae::InputManager::BindCommand(std::unique_ptr<ICommand> command, InputType inputType, unsigned int code, TriggerType triggerType , unsigned int id)
{
	return m_pImpl->BindCommand(std::move(command), inputType,code,triggerType , id);
}
dae::InputManager::~InputManager() = default;