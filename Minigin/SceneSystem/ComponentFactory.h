#pragma once
#include <functional>
#include <map>

#include <nlohmann/json.hpp>

namespace dae {
	class ComponentFactory {
		using BuilderFn = std::function<void(const nlohmann::json&)>;
	private:
		std::unordered_map<std::string, BuilderFn> m_Builders;
	
	public:
		//static ComponentFactory& Get() {
		//	static ComponentFactory instance;
		//	return instance;
		//}


		void Register(std::string name, BuilderFn func);
		void CreateComponent(std::string name, const nlohmann::json&);

	private:
		friend class PrefabFactory;
		ComponentFactory() = default;
	};
}