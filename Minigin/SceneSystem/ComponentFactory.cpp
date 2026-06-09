#include "ComponentFactory.h"

void dae::ComponentFactory::Register(std::string name, BuilderFn func)
{
	m_Builders[name] = func;
}

void dae::ComponentFactory::CreateComponent(std::string name, const nlohmann::json& data)
{
{
	m_Builders[name](data);
}
