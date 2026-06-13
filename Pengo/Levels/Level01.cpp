#include "Level01.h"
#include <SceneSystem/PrefabFactory.h>

#include <ServiceLocator.h>
#include <SoundSystem/ISoundSystem.h>


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
	dae::ServiceLocator<dae::ISoundSystem>::Get().LoadAudio("Data/Audio/Music/MainTheme.mp3" , "theme");
	dae::ServiceLocator<dae::ISoundSystem>::Get().PlayMusic("theme",0.5f);

}
