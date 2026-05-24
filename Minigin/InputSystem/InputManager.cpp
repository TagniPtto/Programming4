
#include "InputManager.h"


#include <glm/vec3.hpp>
#include <SDL3/SDL.h>
#include <backends/imgui_impl_sdl3.h>

#include <vector>


#include "Gamepad/Gamepad.h"
#include "Mouse/Mouse.h"
#include "Keyboard/Keyboard.h"
#include "Commands.h"


dae::InputManager::InputManager() :
	m_pImpl(std::make_unique<dae::InputManagerImpl>())
{
}

bool dae::InputManager::ProcessInput()
{
	return m_pImpl->ProcessInput();
}

void dae::InputManager::BindCommand(std::unique_ptr<ICommand> command, InputBinding binding)
{
	return m_pImpl->BindCommand(std::move(command), binding);
}

void dae::InputManager::BindCommand(std::unique_ptr<ICommand> command, InputType inputType, unsigned int code, InputTriggerType triggerType, unsigned int id)
{
	return m_pImpl->BindCommand(std::move(command), inputType, code, triggerType, id);
}
dae::InputManager::~InputManager() = default;




#define MAX_CONTROLLERS 4

namespace dae {

	class InputManagerImpl final {

	private:
		std::unique_ptr<Mouse> m_mouse;
		std::unique_ptr<Keyboard> m_keyboard;
		std::vector<std::unique_ptr<Gamepad>> m_gamepads;


		std::vector< std::pair<InputBinding, std::unique_ptr<ICommand>>> m_bindings;

	public:
		InputManagerImpl();

		void BindCommand(std::unique_ptr<ICommand>  command, InputBinding binding);
		void BindCommand(std::unique_ptr<ICommand>  command, InputType inputType, unsigned int code, InputTriggerType triggerType, unsigned int id);
		bool ProcessInput();
	private:
		void ProcessBinding(const InputBinding& binding, ICommand* command);
		IInputDevice* GetDevice(InputType deviceType, uint32_t deviceIndex) const;
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
	
	void InputManagerImpl::BindCommand(std::unique_ptr<ICommand>  command, InputType inputType, unsigned int code, InputTriggerType triggerType, unsigned int id)
	{
		InputBinding binding{ .controllerId = id,.type = inputType, .trigger = triggerType ,.code = code};
		BindCommand(std::move(command), binding);
	}
	
	void InputManagerImpl::ProcessGamepadBinding(const InputBinding& binding, ICommand* command)
	{
		if (!(binding.deviceIndex < m_gamepads.size())) {
			return;
		}
		auto& gamepad = m_gamepads[binding.deviceIndex];
		if (binding.deviceValue == InputValueType::Boolean) {
			if ((binding.trigger == InputTriggerType::Held		&&	gamepad->IsHeld(binding.code))||
				(binding.trigger == InputTriggerType::Released	&&	gamepad->IsReleasedThisFrame(binding.code))||
				(binding.trigger == InputTriggerType::Pressed	&&	gamepad->IsPressedThisFrame(binding.code)))
			{
				command->Execute(glm::vec2(1.0f, 0.f));
			}
		}
		if (binding.deviceValue == InputValueType::Float) {
			float value = 0.f;

			if (binding.code == unsigned int(GamepadInput::LeftShoulder)) {
				value = gamepad->GetLeftTrigger();

				if (value > 0.f) {
					command->Execute(glm::vec2(value, 0.f));
				}
			}

			if (binding.code == unsigned int(GamepadInput::RightShoulder)) {
				value = gamepad->GetRightTrigger();

				if (value > 0.f) {
					command->Execute(glm::vec2(value, 0.f));
				}
			}

		}
		if (binding.deviceValue == InputValueType::Vector2) {


			if (binding.code == unsigned int(GamepadInput::LeftThumb)) {
				float x = gamepad->GetLeftThumbX();
				float y = -gamepad->GetLeftThumbY();
				if (x || y) {
					command->Execute(glm::vec2(x, y));
				}
			}
			if(binding.code == unsigned int(GamepadInput::RightThumb)) {
				
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
		if (binding.deviceType == InputType::Keyboard &&
			binding.trigger == InputTriggerType::Held)
		{
			command->Execute(glm::vec2(1.0f, 0.f));
		}
	}	

	void InputManagerImpl::ProcessMouseBinding(const InputBinding& binding, ICommand* command)
	{
		if (binding.trigger == InputTriggerType::Held) {

			float x, y;
			auto buttons = SDL_GetMouseState(&x, &y);
			if (buttons & SDL_BUTTON_MASK(binding.code)) {
				command->Execute(glm::vec2(x, y));
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


		for (auto& [binding, command] : m_bindings)
		{
			ProcessBinding(binding, command);
		}
		return true;
	}

	void InputManagerImpl::ProcessBinding(const InputBinding& binding, ICommand* command)
	{
		IInputDevice* device = GetDevice(binding.deviceType, binding.deviceIndex);

		if (!device) return;

		switch (binding.deviceValue) {
		case InputValueType::Boolean:
			bool triggered{false};

			switch (binding.trigger) {
			case InputTriggerType::Held:
				triggered = device->GetButtonHeld(binding.code);
			break;
			case InputTriggerType::Pressed:
				triggered = device->GetButtonPressed(binding.code);
			break;
			case InputTriggerType::Released:
				triggered = device->GetButtonReleased(binding.code);
			break;
			}
			if (triggered) {
				command->Execute();
			}
		break;
		case InputValueType::Float:
			float value = device->GetAxis1D(binding.code);
			if (value != 0) 
			{
				command->Execute(glm::vec2(value,0));
			}
		break;
		case InputValueType::Vector2:
			glm::vec2 value = device->GetAxis2D(binding.code);
			if (value.x != 0 || value.y != 0)
			{
				command->Execute(value);
			}
		break;
		}
	}

	IInputDevice* dae::InputManagerImpl::GetDevice(InputType deviceType, uint32_t deviceIndex) const
	{
		switch (deviceType) {
		case InputType::Keyboard:
			return m_keyboard;
		case InputType::Mouse:
			return m_mouse;
		case InputType::Gamepad:
			return m_gamepads[deviceIndex].get();
		}
		return nullptr;
	}
}