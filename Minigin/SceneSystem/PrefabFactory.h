#pragma once
#include <functional>
#include <map>

#include <nlohmann/json.hpp>

#include "../Singleton.h"
#include "../GameObject.h"

namespace dae {
	class Scene;
	class PrefabFactory final : public Singleton<PrefabFactory>
	{
	private:
		std::unordered_map<std::string, nlohmann::json> m_Prefabs;
	public:
		bool GetPrefab(std::string name);
		void ApplyOverrides(GameObject& object, const nlohmann::json& data);
		dae::GameObject* Instantiate(dae::Scene& scene,std::string name , const nlohmann::json& instanceData);
		dae::GameObject* Instantiate(dae::Scene& scene, std::string name, glm::vec3 position = {}, float rotation = 0);
	};
}