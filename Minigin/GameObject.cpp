#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float deltaTime)
{
	for (int i{}; i < (int)m_components.size(); i++) {
		m_components[i]->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	for (int i{}; i < (int)m_components.size(); i++) {
		m_components[i]->Render();
	}
}


void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

const glm::vec3& dae::GameObject::GetPosition() const
{
	return m_transform.GetPosition();
}

