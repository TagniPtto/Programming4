#include "playercontrollerComponent.h"

#include "ServiceLocator.h"
#include <SoundSystem/ISoundSystem.h>

#include <InputSystem/InputManager.h>
#include <InputSystem/InputTypes.h>


#include "PlayerCommands.h"


pengo::PlayerControllerComponent::PlayerControllerComponent(dae::GameObject& pawn):
	ObjectComponent(pawn)
{
	dae::ServiceLocator<dae::ISoundSystem>::Get().LoadAudio("Data/SFX/Push_Ice_Block.mp3", "PushIce");


	std::unique_ptr<pengo::MoveCommand> command = std::make_unique<pengo::MoveCommand>(&pawn);
	command->SetMovementSpeed(250.f);
	dae::ServiceLocator<dae::InputManager>::Get().BindCommand(
		std::move(command),
		0,
		dae::InputValueType::Vector2,
		dae::GamepadInput::LeftThumb,
		dae::InputTriggerType::Held);

	auto command2 = std::make_unique<pengo::PlaySoundCommand>();
	dae::ServiceLocator<dae::InputManager>::Get().BindCommand(
		std::move(command2),
		0,
		dae::InputValueType::Boolean,
		dae::GamepadInput::ButtonA,
		dae::InputTriggerType::Pressed);
}

pengo::PlayerControllerComponent::~PlayerControllerComponent()
{

}

void pengo::PlayerControllerComponent::Deserialize(const nlohmann::json&)
{}

void pengo::PlayerControllerComponent::Serialize(nlohmann::json &) const
{}

void pengo::PlayerControllerComponent::Update()
{
}