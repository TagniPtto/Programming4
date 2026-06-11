#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include <ServiceLocator.h>
#include <SceneSystem/ComponentFactory.h>
#include <SceneSystem/SceneManager.h>
#include <SceneSystem/Scene.h>
#include <ResourceSystem/ResourceManager.h>

#include "GridComponent.h"
#include "Player/PlayerControllerComponent.h"
#include "HealthComponent.h"
#include "GridComponent.h"
#include "BlockComponent.h"

#include <filesystem>
namespace fs = std::filesystem;

static void load()
{


	auto& sceneManager =  dae::ServiceLocator<dae::SceneManager>::Get();
	sceneManager.LoadScene("Level0.json");
	//loadedScene;
	//auto& scene = sceneManager.CreateScene();
	//
	//
	//
	//dae::GameObject* grid = scene.CreateGameObject();
	//grid->GetTransform()->SetLocalPosition(150, 150);
	//grid->AddComponent<pengo::GridComponent>("Data/Prefabs/Map.json");
	//
	//dae::GameObject* player = scene.CreateGameObject();
	//player->GetTransform()->SetLocalPosition(150, 150);
	//player->AddComponent<Pengo::PlayerControllerComponent>();
	//auto comp1 = player->AddComponent<dae::RenderComponent>();
	//comp1->SetDestinationRectangle({ 0,0, 25, 25 });
	//auto comp = player->AddComponent<dae::AnimationComponent>("Textures/PengoCharacterSprites.png");
	//comp->AddAnimationSequence({ 0,0, 16 * 40,16 * 18 }, 40, 18, 0, 20, 0.2f, dae::AnimationSequence::AnimationPlayBack::Looped);


}

static void registerComponents() {
	using namespace pengo;

	REGISTER_COMPONENT(PlayerControllerComponent);
	REGISTER_COMPONENT(BlockComponent);
	REGISTER_COMPONENT(GridComponent);
	REGISTER_COMPONENT(HealthComponent);

}

int main(int, char* []) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if (!fs::exists(data_location))
		data_location = "../Data/";
#endif

	registerComponents();

	dae::Minigin engine(data_location);
	engine.Run(load);
	
	return 0;
}
