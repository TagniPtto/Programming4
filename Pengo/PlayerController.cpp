#include "playercontroller.h"

#include <SDL3/SDL.h>
#include "InputSystem/InputManager.h"
#include "InputSystem/gamepad.h"
#include "Commands.h"
#include "ServiceLocator.h"

namespace dae{

	class PlaySoundCommand : public ICommand {
		void Execute(glm::vec2) override
		{
			ServiceLocator::get_sound_system().LoadAudio("Data/SFX/Push_Ice_Block.mp3");
			ServiceLocator::get_sound_system().play(0 , 1);
		}
	};
}	

dae::PlayerController::PlayerController(dae::GameObject& pawn):
	ObjectComponent(pawn)
{
	auto command = std::make_unique<dae::MoveCommand>(&pawn);
	command->SetMovementSpeed(250.f);
	InputManager::GetInstance().BindCommand(std::move(command), InputType::GamepadVector,unsigned int (GamepadInputType::LeftThumb), TriggerType::Held);

	auto command2 = std::make_unique<dae::PlaySoundCommand>();
	InputManager::GetInstance().BindCommand(std::move(command2), InputType::Key,unsigned int (SDL_SCANCODE_A), TriggerType::Held);
}

dae::PlayerController::~PlayerController()
{

}

void dae::PlayerController::Update()
{
}

void dae::PlayerController::Render() const
{
}
