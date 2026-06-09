#pragma once


namespace pengo {
	class PlayerState {
	public:
		virtual ~PlayerState() {};


		virtual void OnEnter();
		virtual void OnExit();

		virtual void HandleInput();
		virtual void Update();
	};
}