#pragma once
#include <Commands.h>
#include "PlayerStateComponent.h"


namespace pengo {

	class PlaySoundCommand : public dae::ICommand {
	public:
		virtual ~PlaySoundCommand() = default;
		void Execute(glm::vec2) override
		{
			dae::ServiceLocator<dae::ISoundSystem>::Get().Play("PushIce", .1f);
		}
	};


	class PlayerStateRequestCommand : public dae::ICommand {
	protected:
		PlayerStateComponent* m_StateComponent;
		PlayerStateRequest m_Request;
	public:
		virtual ~PlayerStateRequestCommand() = default;
		PlayerStateRequestCommand(PlayerStateComponent* stateComponent, PlayerStateRequest request):
			m_StateComponent(stateComponent), m_Request(request)
		{}
		void Execute(glm::vec2 value) override {
			m_StateComponent->HandleRequest(m_Request, value);
		}
	};
}