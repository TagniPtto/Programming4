#include <string>
#include <numbers>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::RemoveChild(GameObject* child)
{
	m_children.erase(
		std::remove(m_children.begin(), m_children.end(), child),
		m_children.end()
	);
}

void dae::GameObject::AddChild(GameObject* child)
{
	m_children.push_back(child);
}

bool dae::GameObject::IsChildOf(GameObject* potentialParent)
{
	if (m_parent == potentialParent)
		return true;
	return false;
}

void dae::GameObject::Update()
{
	for (int i{}; i < (int)m_components.size(); i++) {
		m_components[i]->Update();
	}
}

void dae::GameObject::Render() const
{
	for (int i{}; i < (int)m_components.size(); i++) {
		m_components[i]->Render();
	}
}

dae::GameObject* dae::GameObject::GetParent() const
{
	return m_parent;
}

void dae::GameObject::SetParent(GameObject* newParent , bool keepWorldPosition)
{
	if (m_parent == newParent|| IsChildOf(newParent) || newParent->IsChildOf(this))
		return;

	if (m_parent == nullptr)
		SetLocalPosition(GetWorldPosition());
	else
	{
		if (keepWorldPosition)
			SetLocalPosition(GetWorldPosition() - m_parent->GetWorldPosition());
		SetTransformDirty();
	}

	if (m_parent) m_parent->RemoveChild(this);
	m_parent = newParent;
	if (newParent) newParent->AddChild(this);
}


void dae::GameObject::SetLocalPosition(float x, float y)
{
	SetLocalPosition(glm::vec3(x, y, 0.0f));
}

void dae::GameObject::SetLocalPosition(glm::vec3 pos)
{
	SetTransformDirty();
	m_localtransform.SetPosition(pos);
}

void dae::GameObject::SetLocalRotation(float newRotation)
{
	SetTransformDirty();
	m_localtransform.SetRotation(newRotation);
}

void dae::GameObject::SetLocalTransform(const Transform& newTransform)
{
	SetTransformDirty();
	m_localtransform = newTransform;
}

void dae::GameObject::UpdateWorldTransform()
{


	if (!m_transformDirty)
		return;

	if (m_parent == nullptr)
		m_worldTransform = m_localtransform;
	else {
		m_parent->UpdateWorldTransform();

		float parentRotation = m_parent->GetWorldRotation();
		glm::vec3 localPosition = m_localtransform.GetPosition();
		float radians = glm::radians(parentRotation);

		float cosA = cosf(radians);
		float sinA = sinf(radians);
		glm::vec2 right(cosA, sinA);
		glm::vec2 up(-sinA, cosA);

		glm::vec2 rotated = right * localPosition.x + up * localPosition.y;

		m_worldTransform.SetPosition(m_parent->GetWorldPosition() + glm::vec3(rotated, localPosition.z));
		m_worldTransform.SetRotation(parentRotation + m_localtransform.GetRotation());
	}


	m_transformDirty = false;
}


glm::vec3 dae::GameObject::GetWorldPosition()
{
	return 	GetWorldTransform().GetPosition();
}

float dae::GameObject::GetWorldRotation()
{
	return 	GetWorldTransform().GetRotation();
}

dae::Transform dae::GameObject::GetWorldTransform()
{
	UpdateWorldTransform();
	return m_worldTransform;
}

void dae::GameObject::MarkForDestruction()
{
	m_markedForDestruction = true;
}

bool dae::GameObject::IsMarkedForDestruction() const
{
	return m_markedForDestruction;
}

void dae::GameObject::SetTransformDirty()
{
	m_transformDirty = true;
	for (auto& child : m_children)
	{
		child->SetTransformDirty();
	}
}

