#pragma once
#include <Components/ObjectComponent.h>

namespace pengo {

	class GridMovementComponent : public dae::ObjectComponent {
	public:
		~GridMovementComponent() = default;
		explicit GridMovementComponent(dae::GameObject& owner);
	public:

	};
}