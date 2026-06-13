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
			if (context.binding.deviceValue == dae::InputValueType::Vector2 &&
				(	m_change == PlayerStateChange::MoveUp||
					m_change == PlayerStateChange::MoveDown ||
					m_change == PlayerStateChange::MoveLeft ||
					m_change == PlayerStateChange::MoveRight ))
			{
				auto v = std::get<glm::vec2>(context.value);
				if (std::abs(v.x) < std::abs(v.y))
				{
					m_change = (v.y > 0.0f) ? PlayerStateChange::MoveUp : PlayerStateChange::MoveDown;
				}
				else
				{
					m_change = (v.x > 0.0f) ? PlayerStateChange::MoveRight: PlayerStateChange::MoveLeft;
				}
			}
			m_StateComponent->HandleRequest(m_change);
		}
	};
}