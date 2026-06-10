#pragma once
#include <functional>
#include <map>

#include <nlohmann/json.hpp>
#include "../GameObject.h"

namespace dae {
	class ComponentFactory final {
		using BuilderFn = std::function<void(GameObject& owner, const nlohmann::json&)>;
		std::unordered_map<std::string, BuilderFn> m_Builders;
		
	private:
		ComponentFactory() = default;
	public:

		ComponentFactory(ComponentFactory&&) = delete;
		ComponentFactory(const ComponentFactory&) = delete;
		ComponentFactory& operator=(const ComponentFactory&) = delete;
		ComponentFactory& operator=(ComponentFactory&&) = delete;
		
		static ComponentFactory& Get() {
			static ComponentFactory instance;
			return instance;
		}
		void CreateComponent(const std::string& name, GameObject& owner, const nlohmann::json& instanceData);
		void Register(const std::string& name , BuilderFn builder);
	};
}