#include "PlayerState.h"
#include "PlayerStateComponent.h"

#include <Commands.h>


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
		return std::unique_ptr<PlayerState>();
	}

	std::unique_ptr<PlayerState> MoveState::HandleRequest(
		PlayerStateComponent&,
		dae::InputContext)
	{

		//TODO can get hit by other iceblock from other player.
		return nullptr;
	}
	
	std::unique_ptr<PlayerState> MoveState::Update(PlayerStateComponent&)
	{
		//If reached the tile return to idle.
		// or if new input 
		return nullptr;
	}



}