#include <string>
#include <numbers>
#include "GameObject.h"
#include "Components/TransformComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"


dae::GameObject::GameObject():m_transform(std::make_unique<dae::TransformComponent>(*this))
{
}

dae::GameObject::~GameObject()
{
	SetParent(nullptr); //remove yourself from parent so they dont try to access you after destruction
	for (auto& child : m_children) {
		child->SetParent(nullptr);
	}
}

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
	if (potentialParent == nullptr)
		return false;
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

void dae::GameObject::RenderUI()
{
	for (int i{}; i < (int)m_components.size(); i++) {
		m_components[i]->RenderUI();
	}
}

dae::GameObject* dae::GameObject::GetParent() const
{
	return m_parent;
}

void dae::GameObject::SetParent(GameObject* newParent , bool keepWorldPosition)
{
	if (m_parent == newParent|| IsChildOf(newParent) || (newParent && newParent->IsChildOf(this)))
		return;

	if (m_parent == nullptr) {
		m_transform->SetLocalPosition(m_transform->GetWorldPosition());
	}
	else
	{
		if (keepWorldPosition)
			m_transform->SetLocalPosition(m_transform->GetWorldPosition() - m_parent->GetTransform()->GetWorldPosition());
		m_transform->SetTransformDirty();
	}

	if (m_parent) m_parent->RemoveChild(this);
	m_parent = newParent;
	if (newParent) newParent->AddChild(this);
}

std::vector<dae::GameObject*>& dae::GameObject::GetChildren()
{
	return m_children;
}

dae::TransformComponent* dae::GameObject::GetTransform()
{
	return m_transform.get();
}



void dae::GameObject::MarkForDestruction()
{
	m_markedForDestruction = true;
}

bool dae::GameObject::IsMarkedForDestruction() const
{
	return m_markedForDestruction;
}