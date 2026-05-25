#include "playercontroller.h"

#include "InputSystem/InputManager.h"
#include "InputSystem/InputTypes.h"
#include "Commands.h"
#include "ServiceLocator.h"

namespace Pengo {

	class PlaySoundCommand : public dae::ICommand {
	public:
		~PlaySoundCommand() = default;
		void Execute(glm::vec2) override
		{
			dae::ServiceLocator::get_sound_system().Play("PushIce", .1f);
		}
	};
}	

Pengo::PlayerController::PlayerController(dae::GameObject& pawn):
	ObjectComponent(pawn)
{
	std::unique_ptr<dae::MoveCommand> command = std::make_unique<dae::MoveCommand>(&pawn);
	command->SetMovementSpeed(250.f);
	dae::InputManager::GetInstance().BindCommand(
		std::move(command),
		0,
		dae::InputValueType::Vector2,
		dae::GamepadInput::LeftThumb,
		dae::InputTriggerType::Held);


	dae::ServiceLocator::get_sound_system().LoadAudio("Data/SFX/Push_Ice_Block.mp3","PushIce");

	auto command2 = std::make_unique<Pengo::PlaySoundCommand>();
	dae::InputManager::GetInstance().BindCommand(
		std::move(command2), 
		dae::InputValueType::Boolean, 
		dae::KeyboardInput::KeyA, 
		dae::InputTriggerType::Pressed);
}

Pengo::PlayerController::~PlayerController()
{

}

void Pengo::PlayerController::Update()
{
}

void Pengo::PlayerController::Render() const
{
}
