#pragma once
#include <IInputCommand.h>
#include <GameObject.h>
#include "PlayerStateComponent.h"

namespace pengo {

	class PlayerStateRequestCommand : public dae::IInputCommand {
	protected:
		PlayerStateChange m_change;
		PlayerStateComponent* m_StateComponent;
	public:
		virtual ~PlayerStateRequestCommand() = default;
		PlayerStateRequestCommand(
			PlayerStateComponent* stateComponent,
			PlayerStateChange change):
			m_change(change),
			m_StateComponent(stateComponent)

		{}
		void Execute(dae::InputContext context) override {
			m_StateComponent->HandleRequest(context, m_change);
		}
	};
}