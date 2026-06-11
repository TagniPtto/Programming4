#include "PlayerStateComponent.h"

void pengo::PlayerStateComponent::ChangState(std::unique_ptr<PlayerState> newState)
{
	if (newState) {
		currentState->OnExit(*this);
		currentState = std::move(newState);
		currentState->OnEnter(*this);
	}
}

void pengo::PlayerStateComponent::HandleRequest(PlayerStateRequest request , glm::vec2 value)
{
	auto nextState = currentState->HandleRequest(*this,request, value);
	ChangState(std::move(nextState));
}

void pengo::PlayerStateComponent::Update()
{
	auto nextState = currentState->Update(*this);
	ChangState(std::move(nextState));
}
