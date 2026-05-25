#pragma once
#include "Components/ObjectComponent.h"


namespace Pengo {

	class GameObject;
	
	class PlayerController : public dae::ObjectComponent {

	public:
		explicit PlayerController(dae::GameObject& pawn);
		~PlayerController();

		virtual void Update() override;
		virtual void Render() const override;

	};
}
