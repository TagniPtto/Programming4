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
		PlayerStateRequest , 
		glm::vec2 )
	{
		return std::unique_ptr<PlayerState>();
	}

	std::unique_ptr<PlayerState> MoveState::HandleRequest(
		PlayerStateComponent& stateComponent,
		PlayerStateRequest request, 
		glm::vec2 value)
	{
		value;
		request;
		stateComponent;
		//stateComponent.
		switch (request) {
			case PlayerStateRequest::Interact:
				
				break;
			case PlayerStateRequest::Move:
				break;
			case PlayerStateRequest::Dead:
				break;
		}
		return std::unique_ptr<PlayerState>();
	}
	
	std::unique_ptr<PlayerState> MoveState::Update(PlayerStateComponent& )
	{
		return nullptr;
	}



}