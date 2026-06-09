#include "PrefabFactory.h"


void dae::PrefabFactory::CreatePrefab(std::string name , const nlohmann::json& data)
{
	m_Builders.at(name)(data);
}
