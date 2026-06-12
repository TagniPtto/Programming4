#include "PlayerState.h"
#include "PlayerStateComponent.h"

#include "PlayerCommands.h"


namespace pengo 
{
	void PlayerState::OnEnter(PlayerStateComponent& )
	{}
	void PlayerState::OnExit(PlayerStateComponent& )
	{}
	std::unique_ptr<PlayerState> PlayerState::Update(PlayerStateComponent& )
	{
		return nullptr;
	}


	std::unique_ptr<PlayerState> IdleState::HandleRequest(
		PlayerStateComponent& ,
		dae::InputContext)
	{
		//if (context.binding.) {

		//}
		return std::unique_ptr<PlayerState>();
	}

	std::unique_ptr<PlayerState> IdleState::HandleCommand(pengo::PlayerActionCommand* command)
	{
		//if (pengo::PlayerMoveCommand* com = dynamic_cast<pengo::PlayerMoveCommand*>(command); com) {
		//	//(*com).Execute();
		//}
		return std::unique_ptr<PlayerState>();
	}

	void IdleState::OnEnter(PlayerStateComponent& stateComponent)
	{
		stateComponent.RequestAnimation("Idle");
	}

	std::unique_ptr<PlayerState> MoveState::HandleRequest(
		PlayerStateComponent&,
		dae::InputContext)
	{

		//TODO can get hit by other iceblock from other player.
		return nullptr;
	}

	void MoveState::OnEnter(PlayerStateComponent& stateComponent)
	{
		stateComponent.RequestAnimation("Move");
	}
	
	std::unique_ptr<PlayerState> MoveState::Update(PlayerStateComponent&)
	{
		//If reached the tile return to idle.
		// or if new input 
		return nullptr;
	}



}