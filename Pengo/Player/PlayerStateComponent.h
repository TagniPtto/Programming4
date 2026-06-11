#pragma once
#include <memory>

#include <Components/ObjectComponent.h>
#include "PlayerState.h"

namespace pengo
{
	class PlayerStateComponent : public dae::ObjectComponent {
	private:
		std::unique_ptr<PlayerState> currentState;
	public:
		~PlayerStateComponent() = default;
		explicit PlayerStateComponent(dae::GameObject& owner);
	private:
		void ChangState(std::unique_ptr<PlayerState> newState);
	public:
		void HandleRequest(PlayerStateRequest request, glm::vec2 value);
		void Update() override;

	};
}