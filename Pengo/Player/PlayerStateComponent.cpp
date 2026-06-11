#include "PlayerStateComponent.h"
#include <GameObject.h>
#include <Components/AnimationComponent.h>
#include <Components/TransformComponent.h>
#include "../GridComponent.h"

pengo::PlayerStateComponent::PlayerStateComponent(dae::GameObject& owner, dae::AnimationComponent* anim, dae::TransformComponent* trans) :
	ObjectComponent(owner),
	m_pAnimComp(anim),
	m_pTransformComp(trans)
{
}

void pengo::PlayerStateComponent::ChangState(std::unique_ptr<PlayerState> newState)
{
	if (currentState) 
	{
		currentState->OnExit(*this);
	}
	currentState = std::move(newState);
	if (currentState)
	{
		currentState->OnEnter(*this);
	}
}

void pengo::PlayerStateComponent::HandleRequest(dae::InputContext context)
{
	if (currentState) {
		auto nextState = currentState->HandleRequest(*this,context);
		if (nextState) ChangState(std::move(nextState));
	}
}

void pengo::PlayerStateComponent::Update()
{
	if (currentState) {
		auto nextState = currentState->Update(*this);
		if (nextState) ChangState(std::move(nextState));
	}
}
