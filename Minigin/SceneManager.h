#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Scene.h"
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene();

		void Update();
		void Render();


		Scene* GetCurrentScene();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;


		int m_activeSceneIndex{};
		std::vector<std::unique_ptr<Scene>> m_scenes{};
	};
}
