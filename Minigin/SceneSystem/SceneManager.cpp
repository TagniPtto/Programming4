#include "SceneManager.h"
#include "Scene.h"
#include "PrefabFactory.h"

#include <nlohmann/json.hpp>
#include <fstream>

#include "../ServiceLocator.h"
#include "../LoggingSystem/Logger.h"

void dae::SceneManager::Update()
{
	for(auto& scene : m_scenes)
	{
		scene->Update();
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
		scene->RenderUI();
	}
}

dae::SceneManager::SceneManager():
	m_PrefabFactory(std::make_unique<dae::PrefabFactory>())
{
}

dae::SceneManager::~SceneManager()
{}

dae::Scene& dae::SceneManager::LoadScene(const std::string& path)
{
	auto& scene = CreateScene();

	std::fstream file(path);
	
	if (file.is_open()) {
		const nlohmann::json data = nlohmann::json::parse(file);
		for (const auto& object : data["objects"])
		{

			m_PrefabFactory->CreatePrefab(object);
		}

	}
	else {
		ServiceLocator<Logger>::Get().Write("Failed to Open File : " + path);
	}

	return scene;
}

dae::Scene& dae::SceneManager::CreateScene()
{
	m_scenes.emplace_back(new Scene());
	return *m_scenes.back();
}

dae::Scene* dae::SceneManager::GetScene(int index) const
{
	if (index < m_scenes.size())
	{
		return m_scenes[index].get();
	}
	return nullptr;
}
