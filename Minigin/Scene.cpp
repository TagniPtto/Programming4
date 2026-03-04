#include <algorithm>
#include "GameObject.h"
#include "Scene.h"

using namespace dae;


Scene::Scene():m_rootObject(std::make_unique<GameObject>()){

}

void Scene::Add(std::unique_ptr<GameObject> object)
{
	assert(object != nullptr && "Cannot add a null GameObject to the scene.");
	assert(m_rootObject.get() != nullptr && "Root is Null");
	m_rootObject.get()->SetChild(std::move(object));
}

void Scene::Remove(GameObject& object)
{
	m_rootObject->MarkForDestruction(object);
}

void Scene::RemoveAll()
{
	m_rootObject.reset();
}

void dae::Scene::DestroyMarkedObjects()
{
	m_rootObject->DestroyMarkedChildren();
}

GameObject* dae::Scene::GetRootObject()
{
	return m_rootObject.get();
}

void Scene::Update()
{
	m_rootObject->Update();

	DestroyMarkedObjects();
}

void Scene::Render() const
{
	m_rootObject->Render();
}

