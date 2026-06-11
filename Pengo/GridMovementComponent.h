#pragma once
#include <Components/ObjectComponent.h>
#include <glm/glm.hpp>


namespace dae {
	class GameObject;
}

namespace pengo {
	class GridComponent;

	class GridMovementComponent : public dae::ObjectComponent {
	private:
		GridComponent* m_Grid;

	public:
		~GridMovementComponent() = default;
		explicit GridMovementComponent(dae::GameObject& owner);
	public:

		bool RequestMove(dae::GameObject& object,glm::ivec2 direction);
		void Update(float dt);

	};
}