#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Scene.h"

namespace dae
{
	class Scene;
	class SceneManager final
	{
	public:
		Scene& CreateScene();
		Scene* GetScene(int index) const;

		void Update();
		void Render();
	private:
		friend class Minigin;
		SceneManager() = default;
		std::vector<std::unique_ptr<Scene>> m_scenes{};
	};
}
