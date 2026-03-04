#include <string>
#include <numbers>
#include "GameObject.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Renderer.h"


dae::GameObject::~GameObject() = default;

std::unique_ptr<dae::GameObject> dae::GameObject::RemoveChild(GameObject* childPtr)
{
	auto it = std::find_if(m_children.begin(), m_children.end(), [childPtr](const std::unique_ptr<GameObject>& child) {
		return childPtr == child.get();
		});

	if (it == m_children.end())
		return nullptr;

	std::unique_ptr<GameObject> child = std::move(*it);

	m_children.erase(it);
	return std::move(child);
}

void dae::GameObject::AddChild(std::unique_ptr<GameObject> child)
{
	m_children.emplace_back(std::move(child));
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

void dae::GameObject::SetChild(std::unique_ptr<GameObject> newChild)
{
	newChild->m_parent = this;
	AddChild(std::move(newChild));
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


	std::unique_ptr<GameObject> thisObject;
	if (m_parent) {
		thisObject = m_parent->RemoveChild(this);
	}
	else {
		newParent = SceneManager::GetInstance().GetCurrentScene()->GetRootObject();
		//if no parent get it from the unique ptr from the scene
	}


	m_parent = newParent;

	if (newParent) { 
		newParent->AddChild(std::move(thisObject));
	}
	else {
		//Now the scene will own the gameobject
	}
}


void dae::GameObject::SetLocalPosition(float x, float y)
{
	SetLocalPosition(glm::vec3(x, y, 0.0f));
}

void dae::GameObject::SetLocalPosition(glm::vec3 pos)
{
	SetTransformDirty();
	m_localTransform.SetPosition(pos);
}

void dae::GameObject::SetLocalRotation(float newRotation)
{
	SetTransformDirty();
	m_localTransform.SetRotation(newRotation);
}

void dae::GameObject::SetLocalTransform(const Transform& newTransform)
{
	SetTransformDirty();
	m_localTransform = newTransform;
}

void dae::GameObject::UpdateWorldTransform()
{
	if (!m_transformDirty)
		return;

	if (m_parent == nullptr)
		m_worldTransform = m_localTransform;
	else {
		m_parent->UpdateWorldTransform();

		float parentRotation = m_parent->GetWorldRotation();
		glm::vec3 localPosition = m_localTransform.GetPosition();
		float radians = glm::radians(parentRotation);

		float cosA = cosf(radians);
		float sinA = sinf(radians);
		glm::vec2 right(cosA, sinA);
		glm::vec2 up(-sinA, cosA);

		glm::vec2 rotated = right * localPosition.x + up * localPosition.y;

		m_worldTransform.SetPosition(m_parent->GetWorldPosition() + glm::vec3(rotated, localPosition.z));
		m_worldTransform.SetRotation(parentRotation + m_localTransform.GetRotation());
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

const dae::Transform& dae::GameObject::GetWorldTransform()
{
	UpdateWorldTransform();
	return m_worldTransform;
}

void dae::GameObject::MarkForDestruction(GameObject& child)
{
	if (this == &child) {
		m_markedForDestruction = true;
	}
	else {
		for (auto& obj : m_children)
		{
			obj->MarkForDestruction(child);
		}
	}
}

bool dae::GameObject::IsMarkedForDestruction() const
{
	return m_markedForDestruction;
}

void dae::GameObject::DestroyMarkedChildren()
{
	m_children.erase(std::remove_if(m_children.begin(), m_children.end(), [](const std::unique_ptr<GameObject>& child){
		if (child->IsMarkedForDestruction()) {
			return true;
		}
		else {
			child->DestroyMarkedChildren();
			return false;
		}
		}),
		m_children.end());
}

void dae::GameObject::SetTransformDirty()
{
	m_transformDirty = true;
	for (auto& child : m_children)
	{
		child->SetTransformDirty();
	}
}

