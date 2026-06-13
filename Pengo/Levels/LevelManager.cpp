
#include "LevelManager.h"
#include <ServiceLocator.h>
#include <SceneSystem/SceneManager.h>

void pengo::LevelManager::AddLevel(std::unique_ptr<Level> level)
{
	m_levels.push_back(std::move(level));
}

void pengo::LevelManager::Load(int index)
{
	auto scene = dae::ServiceLocator<dae::SceneManager>::Get().GetActiveScene();
	m_levels[index]->Load(*scene);
}
