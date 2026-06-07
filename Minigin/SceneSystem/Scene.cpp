#include <algorithm>
#include "GameObject.h"
#include "Scene.h"

using namespace dae;


GameObject* Scene::CreateGameObject() 
{
	auto obj = std::make_unique<dae::GameObject>();
	auto objPtr = obj.get();
	Add(std::move(obj));
	return objPtr;
}

void Scene::Add(std::unique_ptr<GameObject> object)
{
	assert(object != nullptr && "Cannot add a null GameObject to the scene.");
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(const GameObject& object)
{
	for (auto& obj : m_objects)
	{
		if (obj.get() == &object)
		{
			obj->MarkForDestruction();
		}
	}
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void dae::Scene::DestroyMarkedObjects()
{
	m_objects.erase(
		std::remove_if(
			m_objects.begin(),
			m_objects.end(),
			[](const auto& ptr) { return ptr->IsMarkedForDestruction(); }
		),
		m_objects.end()
	);
}

void Scene::Update()
{
	for(auto& object : m_objects)
	{
		object->Update();
	}
	DestroyMarkedObjects();
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

void dae::Scene::RenderUI()
{
	for (const auto& object : m_objects)
	{
		object->RenderUI();
	}
}

