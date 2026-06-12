#include "PlayerStateComponent.h"
#include <GameObject.h>
#include <Components/AnimationComponent.h>
#include "../GridMovementComponent.h"

pengo::PlayerStateComponent::PlayerStateComponent(
	dae::GameObject& owner, 
	dae::AnimationComponent* anim, 
	pengo::GridMovementComponent* mov,
	pengo::GridInteractionComponent* in):
	ObjectComponent(owner),
	m_pAnimComp(anim),
	m_pMovementComp(mov),
	m_pInteractionComp(in)
	
{
	if (!m_pAnimComp) {
		m_pAnimComp = m_owner->GetComponent<dae::AnimationComponent>();
	}
	if (!m_pMovementComp) {
		m_pMovementComp = m_owner->GetComponent<GridMovementComponent>();
	}
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

void pengo::PlayerStateComponent::HandleCommand(pengo::PlayerActionCommand* command)
{
	if (currentState) {
		auto nextState = currentState->HandleCommand(command);
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

void pengo::PlayerStateComponent::Deserialize(const nlohmann::json&)
{

}

void pengo::PlayerStateComponent::Serialize(nlohmann::json &) const
{}


void pengo::PlayerStateComponent::RequestPush() const
{

}

void pengo::PlayerStateComponent::RequestAnimation(std::string name) const
{
	if (m_pAnimComp) {
		m_pAnimComp->SetAnimation(name);
	}
}

void pengo::PlayerStateComponent::RequestMove(glm::ivec2 dir) const
{
	if (m_pMovementComp) {
		m_pMovementComp->RequestMove(dir);
	}
}
