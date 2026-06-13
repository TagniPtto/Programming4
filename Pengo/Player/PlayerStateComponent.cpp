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
	m_pCurrentState = std::make_unique<pengo::IdleState>();
}

void pengo::PlayerStateComponent::ChangeState(std::unique_ptr<PlayerState> newState)
{
	if (m_pCurrentState) 
	{
		m_pCurrentState->OnExit(*this);
	}
	m_pCurrentState = std::move(newState);
	if (m_pCurrentState)
	{
		m_pCurrentState->OnEnter(*this);
	}
}

void pengo::PlayerStateComponent::HandleRequest(PlayerStateChange change)
{
	if (m_pCurrentState) {
		auto nextState = m_pCurrentState->HandleRequest(*this, change);
		if (nextState) ChangeState(std::move(nextState));
	}
}

void pengo::PlayerStateComponent::Update()
{
	if (m_pCurrentState) {
		auto nextState = m_pCurrentState->Update(*this);
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