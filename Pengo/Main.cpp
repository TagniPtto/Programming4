#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "Levels/LevelManager.h"
#include "Levels/Level01.h"

#include <SceneSystem/ComponentFactory.h>
#include "Player/PlayerControllerComponent.h"
#include "Player/PlayerStateComponent.h"
#include "GridMovementComponent.h"
#include "GridInteractionComponent.h"
#include "GridComponent.h"
#include "HealthComponent.h"


#include <filesystem>
namespace fs = std::filesystem;

static void load()
{
	pengo::LevelManager::Get().AddLevel(std::make_unique<pengo::Level01>());
	pengo::LevelManager::Get().Load(0);

}

static void registerComponents() {
	using namespace pengo;
	REGISTER_COMPONENT(PlayerControllerComponent);
	REGISTER_COMPONENT(PlayerStateComponent);
	REGISTER_COMPONENT(GridMovementComponent);
	REGISTER_COMPONENT(GridInteractionComponent);
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
