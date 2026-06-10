#include "ComponentFactory.h"

void dae::ComponentFactory::CreateComponent(const std::string& name, GameObject& owner,const nlohmann::json& instanceData)
{
	if (auto it = m_Builders.find(name); it != m_Builders.end()) {
		auto fn = it->second;
		fn(owner, instanceData);
	}
}

void dae::ComponentFactory::Register(const std::string& name, BuilderFn builder)
{
	m_Builders[name] = builder;
}
