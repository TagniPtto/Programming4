#pragma once
#include <memory>
#include <InputSystem/InputTypes.h>

namespace pengo
{
	class AnimationComponent;
	class PlayerStateComponent;
	
	class PlayerState {
	private:
		AnimationComponent* animationComp;
	public:
		virtual ~PlayerState() = default;

		virtual void OnEnter(PlayerStateComponent& stateComponent);
		virtual void OnExit(PlayerStateComponent& stateComponent);

		virtual std::unique_ptr<PlayerState> Update(PlayerStateComponent& stateComponent);
		virtual std::unique_ptr<PlayerState> HandleRequest(
			PlayerStateComponent& stateComponent,
			dae::InputContext context) = 0;
	};

	class IdleState : public PlayerState {
	public:
		virtual ~IdleState() = default;
		virtual std::unique_ptr<PlayerState> HandleRequest(
			PlayerStateComponent& stateComponent, 
			dae::InputContext context);
	};

	class MoveState : public PlayerState {
		//glm::uvec2 dir;
	public:
		virtual ~MoveState() = default;
		virtual std::unique_ptr<PlayerState> Update(PlayerStateComponent& stateComponent) override;
		virtual std::unique_ptr<PlayerState> HandleRequest(
			PlayerStateComponent& stateComponent, 
			dae::InputContext context);
	};

	class DeadState : public PlayerState {
	public:
		virtual ~DeadState() = default;
		virtual void OnEnter(PlayerStateComponent& stateComponent) override;
	};
}