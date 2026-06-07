#include "playercontrollerComponent.h"

#include "ServiceLocator.h"
#include <SoundSystem/ISoundSystem.h>

#include <InputSystem/InputManager.h>
#include <InputSystem/InputTypes.h>
#include <Commands.h>

namespace Pengo {

	class PlaySoundCommand : public dae::ICommand {
	public:
		~PlaySoundCommand() = default;
		void Execute(glm::vec2) override
		{
			dae::ServiceLocator<dae::ISoundSystem>::Get().Play("PushIce", .1f);
		}
	};

	class MoveUnitCommand : public dae::ICommand {
		~MoveUnitCommand() = default;
		void Execute(glm::vec2) override
		{
			//Moving a unit
		}
	};
}	

Pengo::PlayerControllerComponent::PlayerControllerComponent(dae::GameObject& pawn):
	ObjectComponent(pawn)
{
	dae::ServiceLocator<dae::ISoundSystem>::Get().LoadAudio("Data/SFX/Push_Ice_Block.mp3", "PushIce");


	std::unique_ptr<dae::MoveCommand> command = std::make_unique<dae::MoveCommand>(&pawn);
	command->SetMovementSpeed(250.f);
	dae::ServiceLocator<dae::InputManager>::Get().BindCommand(
		std::move(command),
		0,
		dae::InputValueType::Vector2,
		dae::GamepadInput::LeftThumb,
		dae::InputTriggerType::Held);

	auto command2 = std::make_unique<Pengo::PlaySoundCommand>();
	dae::ServiceLocator<dae::InputManager>::Get().BindCommand(
		std::move(command2),
		dae::InputValueType::Boolean,
		dae::KeyboardInput::KeyA,
		dae::InputTriggerType::Pressed);


	
}

Pengo::PlayerControllerComponent::~PlayerControllerComponent()
{

}

void Pengo::PlayerControllerComponent::Update()
{
}