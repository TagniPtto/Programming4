#include "playercontrollerComponent.h"

#include <InputSystem/InputManager.h>
#include <InputSystem/InputTypes.h>


#include "PlayerCommands.h"


pengo::PlayerControllerComponent::PlayerControllerComponent(dae::GameObject& pawn):
	ObjectComponent(pawn)
{


	//std::unique_ptr<pengo::MoveCommand> command = std::make_unique<pengo::MoveCommand>(&pawn);
	//command->SetMovementSpeed(250.f);
	//dae::ServiceLocator<dae::InputManager>::Get().BindCommand(
	//	std::move(command),
	//	0,
	//	dae::InputValueType::Vector2,
	//	dae::GamepadInput::LeftThumb,
	//	dae::InputTriggerType::Held);

	//auto command2 = std::make_unique<pengo::PlaySoundCommand>();
	//dae::ServiceLocator<dae::InputManager>::Get().BindCommand(
	//	std::move(command2),
	//	0,
	//	dae::InputValueType::Boolean,
	//	dae::GamepadInput::ButtonA,
	//	dae::InputTriggerType::Pressed);
}


void pengo::PlayerControllerComponent::Deserialize(const nlohmann::json&)
{
	//auto commandBindings = data["CommandBindings"];

	//for (auto& commandBinding : commandBindings) {
	//	auto& binding = commandBinding["Binding"];
	//	auto& command = commandBinding["Command"];
	//	
	//}
}

void pengo::PlayerControllerComponent::Serialize(nlohmann::json &) const
{}
