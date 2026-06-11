#pragma once

#include "TimeManager.h"
#include "InputSystem/InputTypes.h"

namespace dae{
	class ICommand {
	public:
		virtual ~ICommand() = default;
		virtual void Execute(dae::InputContext context) = 0;
	};

	class GameObject;
	class GameObjectCommand : public ICommand{
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

	class EditorCommand : public ICommand {
	public:
		virtual ~EditorCommand() = default;
		virtual void Undo() = 0;
		virtual void Redo() = 0;

	};
}