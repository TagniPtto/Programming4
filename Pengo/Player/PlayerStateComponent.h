#pragma once
#include <memory>

#include <Components/ObjectComponent.h>
#include "PlayerState.h"

namespace dae {
	class AnimationComponent;
	class TransformComponent;
}
namespace pengo
{

	class PlayerStateComponent : public dae::ObjectComponent {
	private:
		std::unique_ptr<PlayerState> currentState;
	private:
		dae::AnimationComponent* m_pAnimComp{};
		dae::TransformComponent* m_pTransformComp{};
	public:
		~PlayerStateComponent() = default;
		explicit PlayerStateComponent(
			dae::GameObject& owner,
			dae::AnimationComponent* anim,
			dae::TransformComponent* trans);
	private:
		void ChangState(std::unique_ptr<PlayerState> newState);
	public:
		void HandleRequest(dae::InputContext context);
		void Update() override;

	};
}