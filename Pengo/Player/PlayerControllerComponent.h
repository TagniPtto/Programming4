#pragma once
#include "Components/ObjectComponent.h"


namespace pengo {

	class GameObject;
	
	class PlayerControllerComponent : public dae::ObjectComponent {

	public:
		explicit PlayerControllerComponent(dae::GameObject& pawn);
		virtual ~PlayerControllerComponent() = default;
	public:
		virtual void Deserialize(const nlohmann::json& data) override;
		virtual void Serialize(nlohmann::json& data) const override;

	};
}
