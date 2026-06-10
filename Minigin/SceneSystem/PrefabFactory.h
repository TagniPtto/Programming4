#pragma once
#include <functional>
#include <map>

#include <nlohmann/json.hpp>

#include "GameObject.h"

namespace dae {
	class Scene;
	class PrefabFactory final
	{
	private:
		std::unordered_map<std::string, nlohmann::json> m_Prefabs;
	
	private:
		PrefabFactory() = default;
	
	public:
		static PrefabFactory& Get() {
			static PrefabFactory instance;
			return instance;
		}
		PrefabFactory(PrefabFactory&&) = delete;
		PrefabFactory(const PrefabFactory&) = delete;
		PrefabFactory& operator=(PrefabFactory&&) = delete;
		PrefabFactory& operator=(const PrefabFactory&) = delete;

		bool GetPrefab(std::string name);
		dae::GameObject* Instantiate(dae::Scene* scene,std::string name , const nlohmann::json& instanceData);
		dae::GameObject* Instantiate(dae::Scene* scene, std::string name, glm::vec3 position = {}, float rotation = 0);
		void ApplyOverrides(GameObject& object, const nlohmann::json& data);
	};
}