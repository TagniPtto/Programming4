#pragma once
#include <memory>
#include <InputSystem/InputTypes.h>
#include "PlayerCommands.h"

namespace pengo
{
	class PlayerStateComponent;
	
	enum class PlayerStateChange {
		Idle,
		Move,
		Push,
		Death,
	};

	class PlayerState {
	public:
		virtual ~PlayerState() = default;

		virtual void OnEnter(PlayerStateComponent& stateComponent);
		virtual void OnExit(PlayerStateComponent& stateComponent);

		virtual std::unique_ptr<PlayerState> Update(PlayerStateComponent& stateComponent);
		virtual std::unique_ptr<PlayerState> HandleRequest(
			PlayerStateComponent& stateComponent,
			dae::InputContext context) = 0;
		virtual std::unique_ptr<PlayerState> HandleCommand(pengo::PlayerActionCommand* command) = 0;
	};


	class IdleState : public PlayerState {
	public:
		virtual ~IdleState() = default;
		virtual std::unique_ptr<PlayerState> HandleRequest(
			PlayerStateComponent& stateComponent, 
			dae::InputContext context);
		virtual std::unique_ptr<PlayerState> HandleCommand(pengo::PlayerActionCommand* command);
		virtual void OnEnter(PlayerStateComponent& stateComponent) override;
	};


	class MoveState : public PlayerState {
		//glm::uvec2 dir;
	public:
		virtual ~MoveState() = default;
		virtual std::unique_ptr<PlayerState> Update(PlayerStateComponent& stateComponent) override;
		virtual std::unique_ptr<PlayerState> HandleRequest(
			PlayerStateComponent& stateComponent, 
			dae::InputContext context);
		virtual void OnEnter(PlayerStateComponent& stateComponent) override;
	};


	class DeadState : public PlayerState {
	public:
		virtual ~DeadState() = default;
		virtual void OnEnter(PlayerStateComponent& stateComponent) override;
	};
}