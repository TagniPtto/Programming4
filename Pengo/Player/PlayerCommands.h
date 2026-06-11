#pragma once
#include <Commands.h>
#include <GameObject.h>
#include "PlayerStateComponent.h"


namespace pengo {

	class PlaySoundCommand : public dae::ICommand {
	public:
		virtual ~PlaySoundCommand() = default;
		void Execute(dae::InputContext) override
		{
			dae::ServiceLocator<dae::ISoundSystem>::Get().Play("PushIce", .1f);
		}
	};
	class MoveCommand : public dae::GameObjectCommand {
	private:
		float m_speed;
	public:
		virtual ~MoveCommand() = default;
		explicit MoveCommand(dae::GameObject* object) : dae::GameObjectCommand(object), m_speed() {}
		void SetMovementSpeed(float speed) { m_speed = speed; }
		virtual void Execute(dae::InputContext context) override {
			glm::vec2& direction = std::get<glm::vec2>(context.value);
			direction.y *= -1.0f;
			GetGameObject()->GetTransform()->SetLocalPosition(GetGameObject()->GetTransform()->GetLocalPosition() + m_speed * glm::normalize(glm::vec3(direction, 0.0f)) * dae::Time::GetInstance().GetDeltaTime());
		};
	};

	class PlayerStateRequestCommand : public dae::ICommand {
	protected:
		PlayerStateComponent* m_StateComponent;
	public:
		virtual ~PlayerStateRequestCommand() = default;
		PlayerStateRequestCommand(PlayerStateComponent* stateComponent):
			m_StateComponent(stateComponent)
		{}
		void Execute(dae::InputContext context) override {
			m_StateComponent->HandleRequest(context);
		}
	};
}