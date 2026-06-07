#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include <ServiceLocator.h>
#include <SceneSystem/SceneManager.h>
#include <ResourceSystem/ResourceManager.h>
#include "Components/TextComponent.h"
#include "Components/FPSComponent.h"
#include "Components/RenderComponent.h"
#include "Components/RotationComponent.h"
#include "Components/AnimationComponent.h"

#include "GridComponent.h"
#include "PlayerControllerComponent.h"


#include <filesystem>
namespace fs = std::filesystem;

static void load()
{

	auto& scene = dae::ServiceLocator<dae::SceneManager>::Get().CreateScene();
	auto font = dae::ServiceLocator<dae::ResourceManager>::Get().LoadFont("Lingua.otf", 36);

	//auto gto = std::make_unique<dae::GameObject>();
	//gto->GetTransform()->SetLocalPosition(10, 10);
	//gto->AddComponent<dae::FPSComponent>("FPS", font);
	//scene.Add(std::move(gto));

	auto gto = std::make_unique<dae::GameObject>();
	gto->GetTransform()->SetLocalPosition(350, 250);
	gto->AddComponent<Pengo::PlayerControllerComponent>();

	scene.Add(std::move(gto));
	auto grid = std::make_unique<dae::GameObject>();

	grid->AddComponent<pengo::GridComponent>(10 , 10 , 5);
	auto comp1 = grid->AddComponent<dae::RenderComponent>();
	comp1->SetDestinationRectangle({ 0,0, 16 * 10,16 * 10});
	auto comp = grid->AddComponent<dae::AnimationComponent>("PengoCharacterSprites.png");
	comp->AddAnimationSequence({ 0,0, 16 * 40,16 * 18 }, 40, 18, 0, 20, 0.2f, dae::AnimationSequence::AnimationPlayBack::Looped);
	scene.Add(std::move(grid));
}

int main(int, char* []) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if (!fs::exists(data_location))
		data_location = "../Data/";
#endif
	dae::Minigin engine(data_location);
	engine.Run(load);
	return 0;
}
