#include "playercontroller.h"

#include <SDL3/SDL.h>
#include "InputSystem/InputManager.h"
#include "InputSystem/gamepad.h"
#include "Commands.h"

dae::PlayerController::PlayerController(dae::GameObject& pawn):
	ObjectComponent(pawn)
{
	auto command = std::make_unique<dae::MoveCommand>(&pawn);
	command->SetMovementSpeed(250.f);
	InputManager::GetInstance().BindCommand(std::move(command), InputType::GamepadVector,unsigned int (GamepadInputType::LeftThumb), TriggerType::Held);
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
