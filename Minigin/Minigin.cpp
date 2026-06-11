#include <stdexcept>
#include <sstream>
#include <iostream>
#include <thread>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#endif

#include <SDL3/SDL.h>
//#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>

#include "Minigin.h"

#include "Renderer.h"
#include "TimeManager.h"

#include "ServiceLocator.h"
#include "InputSystem/InputManager.h"
#include "SceneSystem/SceneManager.h"
#include "ResourceSystem/ResourceManager.h"
#include "SoundSystem/SDLLoggingSoundSystem.h"
#include "EventSystem/EventQueue.h"
#include "LoggingSystem/Logger.h"

#include "SceneSystem/ComponentFactory.h"

#include "Components/AnimationComponent.h"
#include "Components/RenderComponent.h"
#include "Components/TransformComponent.h"
#include "Components/RotationComponent.h"
#include "Components/TextComponent.h"
#include "Components/FPSComponent.h"


SDL_Window* g_window{};
void RegisterComponents() {
	using namespace dae;
	REGISTER_COMPONENT(AnimationComponent);
	REGISTER_COMPONENT(RenderComponent);
	REGISTER_COMPONENT(TransformComponent);
	REGISTER_COMPONENT(RotationComponent);
	REGISTER_COMPONENT(TextComponent);
	REGISTER_COMPONENT(FPSComponent);
}


void LogSDLVersion(const std::string& message, int major, int minor, int patch)
{
#if WIN32
	std::stringstream ss;
	ss << message << major << "." << minor << "." << patch << "\n";
	OutputDebugString(ss.str().c_str());
#else
	std::cout << message << major << "." << minor << "." << patch << "\n";
#endif
}

#ifdef __EMSCRIPTEN__
#include "emscripten.h"

void LoopCallback(void* arg)
{
	auto lastTime = std::chrono::high_resolution_clock::now();

	static_cast<dae::Minigin*>(arg)->RunOneFrame();

	const auto thisTime = std::chrono::high_resolution_clock::now();
	const float deltaTime = std::chrono::duration<float>(thisTime - lastTime).count();
	lastTime = thisTime;

	dae::Time::GetInstance().Update(deltaTime);

}
#endif

// Why bother with this? Because sometimes students have a different SDL version installed on their pc.
// That is not a problem unless for some reason the dll's from this project are not copied next to the exe.
// These entries in the debug output help to identify that issue.
void PrintSDLVersion()
{
	LogSDLVersion("Compiled with SDL", SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_MICRO_VERSION);
	int version = SDL_GetVersion();
	LogSDLVersion("Linked with SDL ", SDL_VERSIONNUM_MAJOR(version), SDL_VERSIONNUM_MINOR(version), SDL_VERSIONNUM_MICRO(version));
	// LogSDLVersion("Compiled with SDL_image ",SDL_IMAGE_MAJOR_VERSION, SDL_IMAGE_MINOR_VERSION, SDL_IMAGE_MICRO_VERSION);
	// version = IMG_Version();
	// LogSDLVersion("Linked with SDL_image ", SDL_VERSIONNUM_MAJOR(version), SDL_VERSIONNUM_MINOR(version), SDL_VERSIONNUM_MICRO(version));
	LogSDLVersion("Compiled with SDL_ttf ",	SDL_TTF_MAJOR_VERSION, SDL_TTF_MINOR_VERSION,SDL_TTF_MICRO_VERSION);
	version = TTF_Version();
	LogSDLVersion("Linked with SDL_ttf ", SDL_VERSIONNUM_MAJOR(version), SDL_VERSIONNUM_MINOR(version),	SDL_VERSIONNUM_MICRO(version));
}

dae::Minigin::Minigin(const std::filesystem::path& dataPath) :
	m_pResourceManager(new dae::ResourceManager()),
	m_pSceneManager(new dae::SceneManager()),
	m_pInputManager(new dae::InputManager()),
#if DEBUG
	m_pSoundSystem(new dae::SDLLoggingSoundSystem()),
#else
	m_pSoundSystem(new dae::SDLSoundSystem()),
#endif
	m_pEventQueue(new dae::EventQueue()),
	m_pRenderer(new dae::Renderer()),
	m_pLogger(std::make_unique<Logger>())
{
	RegisterComponents();

	PrintSDLVersion();
	
	if (!SDL_InitSubSystem(
		SDL_INIT_VIDEO |
		SDL_INIT_GAMEPAD))
	{
		SDL_Log("Renderer error: %s", SDL_GetError());
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		1444,
		800,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	m_pRenderer->Init(g_window);
	
	m_pResourceManager->Init(dataPath);

	ServiceLocator<dae::ISoundSystem>	::Register(m_pSoundSystem.get());
	ServiceLocator<dae::EventQueue>		::Register(m_pEventQueue.get());
	ServiceLocator<dae::InputManager>	::Register(m_pInputManager.get());
	ServiceLocator<dae::SceneManager>	::Register(m_pSceneManager.get());
	ServiceLocator<dae::ResourceManager>::Register(m_pResourceManager.get());
	ServiceLocator<dae::Renderer>		::Register(m_pRenderer.get());
	ServiceLocator<dae::Logger>			::Register(m_pLogger.get());
}

dae::Minigin::~Minigin()
{
	m_pSoundSystem.reset();
	m_pRenderer->Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run(const std::function<void()>& load)
{
	load();
	

#ifndef __EMSCRIPTEN__

	auto lastTime = std::chrono::high_resolution_clock::now();

	const int msPerFrame = 16;

	while (!m_quit)
	{

		const auto thisTime = std::chrono::high_resolution_clock::now();
		const float deltaTime = std::chrono::duration<float>(thisTime - lastTime).count();
		lastTime = thisTime;

		dae::Time::GetInstance().Update(deltaTime);
		RunOneFrame();

		const auto sleeptime = thisTime + std::chrono::milliseconds(msPerFrame) - std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(sleeptime);
	}

#else
	emscripten_set_main_loop_arg(&LoopCallback, this, 0, true);
#endif

}

void dae::Minigin::RunOneFrame()
{
	m_quit = !m_pInputManager->ProcessInput();
	m_pEventQueue->DispatchEvents();
	m_pSceneManager->Update();
	m_pRenderer->Render();
}
