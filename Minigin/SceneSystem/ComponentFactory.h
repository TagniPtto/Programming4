#pragma once
#include <functional>
#include <map>

#include <nlohmann/json.hpp>

#include "../Singleton.h"
#include "../GameObject.h"

namespace dae {
	class ComponentFactory final : public Singleton<ComponentFactory>
	{
		using BuilderFn = std::function<void(GameObject& owner, const nlohmann::json&)>;
		std::unordered_map<std::string, BuilderFn> m_Builders;
	public:
		void CreateComponent(const std::string& name, GameObject& owner, const nlohmann::json& instanceData);
		void Register(const std::string& name , BuilderFn builder);
	};
}