#pragma once
#include <memory>

#include <Components/ObjectComponent.h>
#include "PlayerState.h"

namespace dae {
	class AnimationComponent;
}

namespace pengo
{
	class GridMovementComponent;
	class GridInteractionComponent;
	class PlayerActionCommand;

	class PlayerStateComponent : public dae::ObjectComponent {
	private:
		std::unique_ptr<PlayerState> currentState;
	private:
		dae::AnimationComponent* m_pAnimComp{};
		GridMovementComponent* m_pMovementComp{};
		GridInteractionComponent* m_pInteractionComp{};
		
	public:
		~PlayerStateComponent() = default;
		explicit PlayerStateComponent(
			dae::GameObject& owner,
			dae::AnimationComponent* anim = nullptr,
			pengo::GridMovementComponent* mov = nullptr,
			pengo::GridInteractionComponent* in = nullptr);
		void Deserialize(const nlohmann::json& data) override;
		void Serialize(nlohmann::json&) const override;

	private:
		void ChangeState(std::unique_ptr<PlayerState> newState);
	public:
		void HandleRequest(dae::InputContext context, PlayerStateChange change);
		void Update() override;

		dae::AnimationComponent* GetAnimationComponent()const;
		pengo::GridMovementComponent* GetGridMovementComponent()const;
		pengo::GridInteractionComponent* GetGridInterationComponent()const;

	};
}