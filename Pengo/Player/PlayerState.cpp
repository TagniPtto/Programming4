#include "PlayerState.h"
#include "PlayerStateComponent.h"

#include "PlayerCommands.h"


#include "ServiceLocator.h"
#include <SoundSystem/ISoundSystem.h>
#include <Components/AnimationComponent.h>
#include "../GridMovementComponent.h"
#include "../GridInteractionComponent.h"


namespace pengo 
{
	void PlayerState::OnEnter(PlayerStateComponent& )
	{}
	void PlayerState::OnExit(PlayerStateComponent& )
	{}
	std::unique_ptr<PlayerState> PlayerState::Update(PlayerStateComponent&)
	{
		return nullptr;
	}


	void IdleState::OnEnter(PlayerStateComponent& stateComponent)
	{
		stateComponent.GetAnimationComponent()->SetAnimation("Idle");
	}


	std::unique_ptr<PlayerState> IdleState::HandleRequest(
		PlayerStateComponent&,
		PlayerStateChange change,
		dae::InputContext context)
	{
		if (change == PlayerStateChange::MoveUp||
			change == PlayerStateChange::MoveDown || 
			change == PlayerStateChange::MoveLeft || 
			change == PlayerStateChange::MoveRight ) {

			auto val = std::get<glm::vec2>(context.value);
			return std::make_unique<MoveState>(val);
		}
		if (change == PlayerStateChange::Death) {
			return std::unique_ptr<DeadState>();
		}
		return nullptr;
	}



	MoveState::MoveState(glm::vec2 d):
		dir(d)
	{}

	void MoveState::OnEnter(PlayerStateComponent& stateComponent)
	{
		stateComponent.GetAnimationComponent()->SetAnimation("Move");
	}
	
	std::unique_ptr<PlayerState> MoveState::Update(PlayerStateComponent& stateComp)
	{
		if (stateComp.GetGridMovementComponent()->IsMoving()) {
			return std::unique_ptr<IdleState>();
		}
		return nullptr;
	}

	std::unique_ptr<PlayerState> MoveState::HandleRequest(
		PlayerStateComponent&,
		PlayerStateChange change,
		dae::InputContext)
	{
		if (change == PlayerStateChange::Death) {
			return std::unique_ptr<DeadState>();
		}
		return nullptr;
	}


	void DeadState::OnEnter(PlayerStateComponent& stateComponent)
	{
		stateComponent.GetAnimationComponent()->SetAnimation("Death");
	}

	void PushState::OnEnter(PlayerStateComponent& stateComponent)
	{
		dae::ServiceLocator<dae::ISoundSystem>::Get().LoadAudio("Data/SFX/Push_Ice_Block.mp3", "PushIce");
		stateComponent.GetGridInterationComponent()->RequestPush();
	}

	std::unique_ptr<PlayerState> PushState::HandleRequest(PlayerStateComponent& stateComponent, pengo::PlayerStateChange change, dae::InputContext context)
	{
		if (change == PlayerStateChange::Death) {
			return std::unique_ptr<DeadState>();
		}
		return nullptr;
	}

}