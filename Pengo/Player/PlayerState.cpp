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
		stateComponent.GetAnimationComponent()->PauseCurrentAnimation();
	}


	std::unique_ptr<PlayerState> IdleState::HandleRequest(
		PlayerStateComponent&,
		PlayerStateChange change,
		dae::InputContext)
	{

		if (change == PlayerStateChange::MoveUp||
			change == PlayerStateChange::MoveDown || 
			change == PlayerStateChange::MoveLeft || 
			change == PlayerStateChange::MoveRight ) {
			return std::make_unique<MoveState>(change);
		}
		if (change == PlayerStateChange::Death) {
			return std::make_unique<DeadState>();
		}
		return nullptr;
	}



	MoveState::MoveState(PlayerStateChange direction):
		changeDirection(direction)
	{}

	void MoveState::OnEnter(PlayerStateComponent& stateComponent)
	{
		if (changeDirection == PlayerStateChange::MoveUp)
		{
			stateComponent.GetAnimationComponent()->PlayAnimation("MoveUp");
			stateComponent.GetGridMovementComponent()->RequestMove(glm::ivec2(0,-1));
		}
		if (changeDirection == PlayerStateChange::MoveDown) {
			stateComponent.GetAnimationComponent()->PlayAnimation("MoveDown");
			stateComponent.GetGridMovementComponent()->RequestMove(glm::ivec2(0, 1));
		}
		if (changeDirection == PlayerStateChange::MoveLeft) {
			stateComponent.GetAnimationComponent()->PlayAnimation("MoveLeft");
			stateComponent.GetGridMovementComponent()->RequestMove(glm::ivec2(-1, 0));
		}

		if (changeDirection == PlayerStateChange::MoveRight) {
			stateComponent.GetAnimationComponent()->PlayAnimation("MoveRight");
			stateComponent.GetGridMovementComponent()->RequestMove(glm::ivec2(1, 0));
		}

	}
	
	std::unique_ptr<PlayerState> MoveState::Update(PlayerStateComponent& stateComp)
	{
		if (!stateComp.GetGridMovementComponent()->IsMoving()) {
			return std::make_unique<IdleState>();
		}
		return nullptr;
	}

	std::unique_ptr<PlayerState> MoveState::HandleRequest(
		PlayerStateComponent&,
		PlayerStateChange change,
		dae::InputContext)
	{
		if (change == PlayerStateChange::Death) {
			return std::make_unique<DeadState>();
		}
		return nullptr;
	}



	void PushState::OnEnter(PlayerStateComponent& stateComponent)
	{
		dae::ServiceLocator<dae::ISoundSystem>::Get().LoadAudio("Data/SFX/Push_Ice_Block.mp3", "PushIce");
		stateComponent.GetGridInterationComponent()->RequestPush();
	}

	std::unique_ptr<PlayerState> PushState::HandleRequest(PlayerStateComponent&, pengo::PlayerStateChange change, dae::InputContext)
	{
		if (change == PlayerStateChange::Death) {
			return std::unique_ptr<DeadState>();
		}
		return nullptr;
	}

	void DeadState::OnEnter(PlayerStateComponent& stateComponent)
	{
		stateComponent.GetAnimationComponent()->PlayAnimation("Death");
	}

	std::unique_ptr<PlayerState> DeadState::HandleRequest(
		PlayerStateComponent& , 
		pengo::PlayerStateChange ,
		dae::InputContext )
	{
		return nullptr;
	}
}