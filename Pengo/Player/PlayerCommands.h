#pragma once
#include <IInputCommand.h>
#include <GameObject.h>
#include "PlayerStateComponent.h"

namespace pengo {

	class PlayerActionCommand{
	public:
		virtual ~PlayerActionCommand() = default;
		virtual void Execute(PlayerStateComponent*) = 0;
	};
	class PlayerMoveCommand: public PlayerActionCommand {
		glm::ivec2 direction;
	public:
		virtual ~PlayerMoveCommand() = default;
		virtual void SetDirection(glm::ivec2 d) {
			direction = d;
		}
		virtual void Execute(PlayerStateComponent* comp) {
			comp->RequestMove(glm::ivec2{});
		}
	};
	class PlayerPushCommand : public PlayerActionCommand {
	public:
		virtual ~PlayerPushCommand() = default;
		virtual void Execute(PlayerStateComponent* comp) {
			comp->RequestPush();
		}
	};


	enum class PlayerStateChange {
		Idle,
		Move,
		Push,
		Death,
	};


	class PlayerStateRequestCommand : public dae::IInputCommand {
	protected:
		PlayerStateComponent* m_StateComponent;
	public:
		virtual ~PlayerStateRequestCommand() = default;
		PlayerStateRequestCommand(
			PlayerStateComponent* stateComponent,
			PlayerActionCommand* command):
			m_StateComponent(stateComponent)
		{}
		void Execute(dae::InputContext) {
		}
	};
}