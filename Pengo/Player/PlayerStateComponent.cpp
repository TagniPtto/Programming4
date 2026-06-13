#include "PlayerStateComponent.h"
#include <GameObject.h>
#include <Components/AnimationComponent.h>

#include "../GridMovementComponent.h"
#include "../GridInteractionComponent.h"

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
	if (!m_pInteractionComp) {
		m_pInteractionComp = m_owner->GetComponent<GridInteractionComponent>();
	}
}

void pengo::PlayerStateComponent::ChangeState(std::unique_ptr<PlayerState> newState)
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

void pengo::PlayerStateComponent::HandleRequest(dae::InputContext context, PlayerStateChange change)
{
	if (currentState) {
		auto nextState = currentState->HandleRequest(*this, change,context);
		if (nextState) ChangeState(std::move(nextState));
	}
}

void pengo::PlayerStateComponent::Update()
{
	if (currentState) {
		auto nextState = currentState->Update(*this);
		if (nextState) ChangeState(std::move(nextState));
	}
}

dae::AnimationComponent* pengo::PlayerStateComponent::GetAnimationComponent() const
{
	return m_pAnimComp;
}

pengo::GridMovementComponent* pengo::PlayerStateComponent::GetGridMovementComponent() const
{
	return m_pMovementComp;
}

pengo::GridInteractionComponent* pengo::PlayerStateComponent::GetGridInterationComponent() const
{
	return m_pInteractionComp;
}



void pengo::PlayerStateComponent::Deserialize(const nlohmann::json&)
{}

void pengo::PlayerStateComponent::Serialize(nlohmann::json&) const
{}