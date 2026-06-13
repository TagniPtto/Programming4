#pragma once
#include <memory>
#include <InputSystem/InputTypes.h>
namespace pengo
{
	class PlayerStateComponent;


	enum class PlayerStateChange {
		Idle,
		MoveUp,
		MoveDown,
		MoveLeft,
		MoveRight,
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
			pengo::PlayerStateChange change,
			dae::InputContext context) = 0;
	};


	class IdleState : public PlayerState {
	public:
		virtual ~IdleState() = default;
		virtual void OnEnter(PlayerStateComponent& stateComponent) override;
		virtual std::unique_ptr<PlayerState> HandleRequest(
			PlayerStateComponent& stateComponent, 
			pengo::PlayerStateChange change,
			dae::InputContext context);
	};


	class MoveState : public PlayerState {
		glm::vec2 dir;
	public:
		explicit MoveState(glm::vec2);
		virtual ~MoveState() = default;
		virtual void OnEnter(PlayerStateComponent& stateComponent) override;
		virtual std::unique_ptr<PlayerState> Update(PlayerStateComponent& stateComponent) override;
		virtual std::unique_ptr<PlayerState> HandleRequest(
			PlayerStateComponent& stateComponent, 
			PlayerStateChange change,
			dae::InputContext context);
	};
	class PushState : public PlayerState {
	public:
		virtual ~PushState() = default;
		virtual void OnEnter(PlayerStateComponent& stateComponent) override;
		virtual std::unique_ptr<PlayerState> HandleRequest(
			PlayerStateComponent& stateComponent,
			pengo::PlayerStateChange change,
			dae::InputContext context);
	};

	class DeadState : public PlayerState {
	public:
		virtual ~DeadState() = default;
		virtual void OnEnter(PlayerStateComponent& stateComponent) override;
	};
}