#include "PrefabFactory.h"
#include "ComponentFactory.h"
#include "Scene.h"
#include <fstream>


dae::GameObject* dae::PrefabFactory::Instantiate(dae::Scene* scene,std::string name, const nlohmann::json& instanceData)
{
	dae::GameObject* object = Instantiate(scene, name);

	ApplyOverrides(*object, instanceData);
	
	return object;
}

dae::GameObject* dae::PrefabFactory::Instantiate(dae::Scene* scene, std::string name, glm::vec3 position, float rotation)
{
	if (!GetPrefab(name))
	{
		return nullptr;
	}

	const auto& prefab = m_Prefabs[name];
	GameObject* object = scene->CreateGameObject();
	
	auto transform = object->GetTransform();
	transform->SetLocalPosition(position);
	transform->SetLocalRotation(rotation);
	
	auto& compFactory = ComponentFactory::Get();
	for (const auto& componentJson : prefab["components"])
	{
		auto componentTypeName = std::string(componentJson["type"]) + "Component";
		compFactory.CreateComponent(componentTypeName, *object, componentJson);
	}
	return object;
}

void dae::PrefabFactory::ApplyOverrides(GameObject& object, const nlohmann::json& data)
{
	if (auto it = data.find("position"); it != data.end()) {
		auto& pos = *it;
		object.GetTransform()->SetLocalPosition(pos[0], pos[1]);
	}
}

bool dae::PrefabFactory::GetPrefab(std::string name)
{
	auto it = m_Prefabs.find(name);

	if (it == m_Prefabs.end())
	{
		std::fstream prefabFile("Data/Prefabs/" + name + ".json");
		if (prefabFile.is_open())
		{
			m_Prefabs[name] = nlohmann::json::parse(prefabFile);
			return true;
		}
		else {
			return false;
		}
	}

	return true;
}
