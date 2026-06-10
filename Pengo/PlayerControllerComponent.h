#pragma once
#include "Components/ObjectComponent.h"


namespace pengo {

	class GameObject;
	
	class PlayerControllerComponent : public dae::ObjectComponent {

	public:
		explicit PlayerControllerComponent(dae::GameObject& pawn);
		~PlayerControllerComponent();

		virtual void Update() override;

	};
}
