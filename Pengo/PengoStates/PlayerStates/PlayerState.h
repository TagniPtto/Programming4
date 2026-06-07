#pragma once


namespace pengo {
	class PlayerState {
	public:
		virtual ~PlayerState() {};

		virtual void HandleInput();
		virtual void Update();
		virtual void OnEnter();
		virtual void OnExit();
	};
}