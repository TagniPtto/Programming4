
#include "InputManager.h"


#include <SDL3/SDL.h>
#include <backends/imgui_impl_sdl3.h>

#include <vector>
#include "Gamepad.h"
#include "Commands.h"



namespace dae {

	class InputManagerImpl final {

	private:
		std::vector<std::unique_ptr<Gamepad>> m_gamepads;
		std::vector<InputBinding> m_bindings;

		std::unordered_map<int, int> m_triggerMappings{
			{SDL_EVENT_KEY_DOWN,			int(TriggerType::Pressed)},
			{SDL_EVENT_KEY_UP,				int(TriggerType::Released)},
			{SDL_EVENT_MOUSE_BUTTON_DOWN,	int(TriggerType::Pressed)},
			{SDL_EVENT_MOUSE_BUTTON_UP,		int(TriggerType::Released)},
			{SDL_EVENT_GAMEPAD_BUTTON_UP,	int(TriggerType::Released)},
			{SDL_EVENT_GAMEPAD_BUTTON_DOWN,	int(TriggerType::Pressed)},
		};
	public:
		InputManagerImpl();

		void BindCommand(InputBinding binding);
		void BindCommand(std::unique_ptr<Command>  command, InputType inputType, unsigned int code, TriggerType triggerType, unsigned int id);
		bool ProcessInput();
	};

	InputManagerImpl::InputManagerImpl()
	{
		m_gamepads.emplace_back(std::make_unique<dae::Gamepad>(0));
		m_gamepads.emplace_back(std::make_unique<dae::Gamepad>(1));
		m_gamepads.emplace_back(std::make_unique<dae::Gamepad>(2));
		m_gamepads.emplace_back(std::make_unique<dae::Gamepad>(3));
	}


	void InputManagerImpl::BindCommand(InputBinding binding)
	{
		m_bindings.push_back(std::move(binding));
	}

	void InputManagerImpl::BindCommand(std::unique_ptr<Command>  command, InputType inputType, unsigned int code, TriggerType triggerType, unsigned int id)
	{
		BindCommand({ .controllerId = id,.type = inputType, .trigger = triggerType ,.code = code, .command = std::move(command) });
	}

	bool InputManagerImpl::ProcessInput()
	{
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_QUIT) {
				return false;
			}
			for (auto& binding : m_bindings) {
				switch (binding.type)
				{
				case InputType::Key:
				case InputType::MouseButton:
					if (m_triggerMappings.contains(e.type) && m_triggerMappings[e.type] == int(binding.trigger) && unsigned int(e.key.scancode) == binding.code) {
						binding.command->Execute(glm::vec2(1.0f, 0.f));
					}
					break;
					//case InputType::GamepadButton:
					//	break;
					//case InputType::GamepadValue:
					//	break;
					//case InputType::GamepadVector:
					//	break;
					//default:
					//	break;
				}
			}
			ImGui_ImplSDL3_ProcessEvent(&e);
		}

		for (auto& gamepad : m_gamepads) {
			gamepad->ProcessInput();
		}

		int numberOfKeys;
		const bool* keys = SDL_GetKeyboardState(&numberOfKeys);
		for (auto& binding : m_bindings) {
			if (binding.type == InputType::Key && binding.trigger == TriggerType::Held && unsigned int(binding.code) < unsigned int(numberOfKeys) && keys[binding.code]) {
				binding.command->Execute(glm::vec2(1.0f, 0.f));
			}
			if (binding.type == InputType::MouseButton && binding.trigger == TriggerType::Held) {
				float x, y;
				auto buttons = SDL_GetMouseState(&x, &y);
				if (buttons & SDL_BUTTON_MASK(binding.code)) {
					binding.command->Execute(glm::vec2(x, y));
				}
			}

			for (auto& gamepad : m_gamepads)
			{
				if (gamepad->GetId() == binding.controllerId) {
					if (binding.type == InputType::GamepadInputType) {
						switch (binding.trigger) {
						case TriggerType::Held:
							if (gamepad->IsHeld(binding.code)) {
								binding.command->Execute(glm::vec2(1.0f, 0.f));
							}
							break;
						case TriggerType::Released:
							if (gamepad->IsReleasedThisFrame(binding.code)) {
								binding.command->Execute(glm::vec2(1.0f, 0.f));
							}
							break;
						case TriggerType::Pressed:
							if (gamepad->IsPressedThisFrame(binding.code)) {
								binding.command->Execute(glm::vec2(1.0f, 0.f));
							}
							break;
						default:
							break;
						}
					}
					if (binding.type == InputType::GamepadValue) {
						float value = 0.f;
						switch (binding.code)
						{
							case unsigned int(GamepadInputType::LeftShoulder) :
								value = gamepad->IsHeld(binding.code) ? 1.f : 0.f;
								break;
								case unsigned int(GamepadInputType::RightShoulder) :
									value = gamepad->IsHeld(binding.code) ? 1.f : 0.f;
									break;
								default:
									break;
						}
						if (value > 0.f) {
							binding.command->Execute(glm::vec2(value, 0.f));
						}
					}
					if (binding.type == InputType::GamepadVector) {
						float x = 0.f, y = 0.f;
						switch (binding.code)
						{
							case unsigned int(GamepadInputType::LeftThumb) : // Left Thumb
								x = gamepad->GetLeftThumbX();
								y = -gamepad->GetLeftThumbY();
								break;
								case unsigned int(GamepadInputType::RightThumb) : // Right Thumb
									x = gamepad->GetRightThumbX();
									y = -gamepad->GetRightThumbY();
									break;
								default:
									break;
						}
						if (glm::length(glm::vec2(x, y)) > 0.5f) {
							binding.command->Execute(glm::vec2(x, y));
						}
					}
				}
			}

		}
		return true;
	}
}
dae::InputManager::~InputManager() = default;
dae::InputManager::InputManager():m_pImpl(std::make_unique<dae::InputManagerImpl>()) {
}

bool dae::InputManager::ProcessInput()
{
	return m_pImpl->ProcessInput();
}

void dae::InputManager::BindCommand(InputBinding binding)
{
	return m_pImpl->BindCommand(std::move(binding));
}

void dae::InputManager::BindCommand(std::unique_ptr<Command> command, InputType inputType, unsigned int code, TriggerType triggerType , unsigned int id)
{
	return m_pImpl->BindCommand(std::move(command), inputType,code,triggerType , id);
}
