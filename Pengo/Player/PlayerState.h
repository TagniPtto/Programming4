#pragma once
#include <memory>
#include <glm/glm.hpp>

namespace pengo {

	enum class PlayerStateRequest {
		Interact,
		Move,
		Dead,
	};
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
			PlayerStateRequest request, 
			glm::vec2 value) = 0;
	};

	class IdleState : public PlayerState {
	public:
		virtual ~IdleState() = default;
		virtual std::unique_ptr<PlayerState> HandleRequest(
			PlayerStateComponent& stateComponent, 
			PlayerStateRequest request, 
			glm::vec2 value);
	};

	class MoveState : public PlayerState {
		//glm::uvec2 dir;
	public:
		virtual ~MoveState() = default;
		virtual std::unique_ptr<PlayerState> Update(PlayerStateComponent& stateComponent) override;
		virtual std::unique_ptr<PlayerState> HandleRequest(
			PlayerStateComponent& stateComponent, 
			PlayerStateRequest request, 
			glm::vec2 value);
	};

	class DeadState : public PlayerState {
	public:
		virtual ~DeadState() = default;
		virtual void OnEnter(PlayerStateComponent& stateComponent) override;
	};
}