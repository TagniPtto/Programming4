#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Components/BenchMarkComponent.h"
#include "Components/TextComponent.h"
#include "Components/FPSComponent.h"
#include "Components/RenderComponent.h"
#include "Components/RotationComponent.h"
#include "Scene.h"

#include <filesystem>
namespace fs = std::filesystem;

static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();

	auto go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>("background.png");
	//go->SetTexture("background.png");
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>("logo.png");
	//go->SetTexture("logo.png");
	go->GetTransform()->SetLocalPosition(358, 180);
	scene.Add(std::move(go));

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto gto = std::make_unique<dae::GameObject>();
	gto->GetTransform()->SetLocalPosition(292, 20);
	gto->AddComponent<dae::TextComponent>("Programming 4 Assignment", font);
	auto component = gto->GetComponent<dae::TextComponent>();
	component->SetColor({ 255, 255, 0, 255 });
	scene.Add(std::move(gto));

	gto = std::make_unique<dae::GameObject>();
	gto->GetTransform()->SetLocalPosition(10, 10);
	gto->AddComponent<dae::FPSComponent>("FPS",font);
	scene.Add(std::move(gto));

	gto = std::make_unique<dae::GameObject>();
	gto->GetTransform()->SetLocalPosition(350 , 250);
	gto->AddComponent<dae::RotationComponent>(10.f);
	gto->AddComponent<dae::RenderComponent>("PengoCharacterSprites.png" , .2f);

	auto child = std::make_unique<dae::GameObject>();
	child->GetTransform()->SetLocalPosition(200, 100);
	child->AddComponent<dae::RotationComponent>(-15.f);
	child->AddComponent<dae::RenderComponent>("Jarvis.png" , .5f);

	child->SetParent(gto.get());

	scene.Add(std::move(child));
	scene.Add(std::move(gto));



}

int main(int, char*[]) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif
	dae::Minigin engine(data_location);
	engine.Run(load);
    return 0;
}
