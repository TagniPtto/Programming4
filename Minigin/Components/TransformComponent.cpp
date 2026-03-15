#include "Components/TransformComponent.h"
#include "GameObject.h"


void dae::TransformComponent::SetLocalPosition(float x, float y, float z)
{
	SetLocalPosition(glm::vec3(x, y, z));
}	

void dae::TransformComponent::SetLocalPosition(const glm::vec3& newPosition)
{
	m_localPosition = newPosition;
	SetTransformDirty();
}

void dae::TransformComponent::SetLocalRotation(float newRotation)
{
	m_localRotation = newRotation;
	SetTransformDirty();
}

float dae::TransformComponent::GetLocalRotation() const
{
	return m_localRotation;
}

float dae::TransformComponent::GetWorldRotation() const
{
	UpdateWorldTransform();
	return m_worldRotation;
}
dae::TransformComponent::TransformComponent(dae::GameObject& owner):
	ObjectComponent(owner)
{
}
glm::vec3 dae::TransformComponent::GetLocalPosition() const {
	return m_localPosition;
}

glm::vec3 dae::TransformComponent::GetWorldPosition() const
{
	UpdateWorldTransform();
	return m_worldPosition;
}
void dae::TransformComponent::SetTransformDirty()
{
	m_transformDirty = true;
	for (auto& child : m_owner->GetChildren()) {
		child->GetTransform()->SetTransformDirty();
	}
}
void dae::TransformComponent::UpdateWorldTransform() const
{
	if (!m_transformDirty)
		return;
	GameObject* parent = m_owner->GetParent();
	if (parent == nullptr) {
		m_worldPosition = m_localPosition;
		m_worldRotation = m_localRotation;
	}
	else {

		float parentRotation = parent->GetTransform()->GetWorldRotation();
		glm::vec3 localPosition = parent->GetTransform()->GetLocalPosition();
		float radians = glm::radians(parentRotation);

		float cosA = cosf(radians);
		float sinA = sinf(radians);
		glm::vec2 right(cosA, sinA);
		glm::vec2 up(-sinA, cosA);

		glm::vec2 rotated = right * localPosition.x + up * localPosition.y;
		

		m_worldPosition = parent->GetTransform()->GetWorldPosition() + glm::vec3(rotated, localPosition.z);
		m_worldRotation = parentRotation + m_localRotation;
	}


	m_transformDirty = false;
}