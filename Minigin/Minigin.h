#pragma once
#include <string>
#include <functional>
#include <filesystem>

namespace dae
{
	class ISoundSystem;
	class EventQueue;
	class ResourceManager;
	class SceneManager;
	class InputManager;
	class Renderer;
	class Logger;


	class Minigin final
	{
		std::unique_ptr<ResourceManager> m_pResourceManager;
		std::unique_ptr<SceneManager> m_pSceneManager;
		std::unique_ptr<InputManager> m_pInputManager;
		std::unique_ptr<ISoundSystem> m_pSoundSystem;
		std::unique_ptr<EventQueue> m_pEventQueue;
		std::unique_ptr<Renderer> m_pRenderer;
		std::unique_ptr<Logger> m_pLogger;

		bool m_quit{};
	public:
		explicit Minigin(const std::filesystem::path& dataPath);
		~Minigin();
		void Run(const std::function<void()>& load);
		void RunOneFrame();

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;
	};
}