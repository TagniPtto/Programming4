#pragma once
#include <glm/glm.hpp>
#include "ObjectComponent.h"

namespace dae
{
	class TransformComponent final : public ObjectComponent
	{
	public:
		explicit TransformComponent(dae::GameObject& owner);
		glm::vec3 GetLocalPosition() const;
		glm::vec3 GetWorldPosition() const;
		void SetLocalPosition(float x, float y, float z = 0);
		void SetLocalPosition(glm::vec3 position);


		void SetLocalRotation(float newRotation);
		float GetLocalRotation()const;
		float GetWorldRotation()const;

		void SetTransformDirty();
		void UpdateWorldTransform() const;
	private:
		mutable bool m_transformDirty{ false };

		glm::vec3 m_localPosition{};
		mutable glm::vec3 m_worldPosition{};
		float m_localRotation{};
		mutable float m_worldRotation{};
	};
}
