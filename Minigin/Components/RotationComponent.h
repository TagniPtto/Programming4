#pragma once


#include "ObjectComponent.h"
#include <glm/glm.hpp>

namespace dae {
	class RotationComponent : public ObjectComponent {
	private:
		float m_frequency{};
		float m_currentAngle{};

	public:

		RotationComponent(GameObject& owner, float frequency = 0);
		void Update();

	};
}
