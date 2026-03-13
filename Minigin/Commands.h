#pragma once

#include "GameObject.h"

namespace dae{
	class Command {
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;
	};

	class GameObjectCommand : public Command{
	private:
		GameObject* pObject;
	protected:
		GameObject* GetGameObject() const { return pObject; }
	public:
		virtual void ~GameObjectCommand() = default;
		GameObjectCommand(GameObject* object);
	};

	class EditorCommand : public Command {
	public:
		virtual void ~EditorCommand() = default;
		virtual void Undo() = 0;
		virtual void Redo() = 0;

	};

	class MoveCommand : public GameObjectCommand {
		virtual void Execute() override {
			GetGameObject()->SetLocalPosition(GetGameObject()() + );
		};
	};
}