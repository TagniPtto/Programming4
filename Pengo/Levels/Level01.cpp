#include "Level01.h"
#include <SceneSystem/PrefabFactory.h>


void pengo::Level01::Load(dae::Scene&, GameMode mode)
{
	auto& factory = dae::PrefabFactory::Get();
	auto& sceneManager = dae::ServiceLocator<dae::SceneManager>::Get();
	auto& scene = sceneManager.LoadScene("Scene0.json");
	bool foundPlayerPrefab = factory.GetPrefab("Player");
	if (!foundPlayerPrefab) return;

	if (mode == GameMode::SinglePlayer) {
		
		dae::PrefabFactory::Get().Instantiate(scene,"Player");
	}


}
