#pragma once

#include "GameObject.h"
#include "TimeManager.h"
#include <glm/vec2.hpp>

namespace dae{
	class Command {
	public:
		virtual ~Command() = default;
		virtual void Execute(glm::vec2 input) = 0;
	};

	class GameObjectCommand : public Command{
	private:
		GameObject* m_pObject;
	protected:
		GameObject* GetGameObject() const { return m_pObject; }
	public:
		virtual ~GameObjectCommand() = default;
		explicit GameObjectCommand(GameObject* object):
			m_pObject(object){

		}
	};

	class EditorCommand : public Command {
	public:
		virtual ~EditorCommand() = default;
		virtual void Undo() = 0;
		virtual void Redo() = 0;

	};

	class MoveCommand : public GameObjectCommand {
	private:
		float m_speed;
	public:
		virtual ~MoveCommand() = default;
		explicit MoveCommand(GameObject* object) : GameObjectCommand(object), m_speed() {}
		void SetMovementSpeed(float speed) { m_speed = speed; }
		virtual void Execute(glm::vec2 direction) override {
			GetGameObject()->GetTransform()->SetLocalPosition(GetGameObject()->GetTransform()->GetLocalPosition() + m_speed * glm::normalize(glm::vec3(direction, 0.0f)) * dae::Time::GetInstance().GetDeltaTime());
		};
	};
}