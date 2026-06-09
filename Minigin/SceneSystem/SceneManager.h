#pragma once
#include <vector>
#include <string>
#include <memory>

namespace dae
{
	class Scene;
	class PrefabFactory;
	class SceneManager final
	{
	public:
		~SceneManager();

		Scene& LoadScene(const std::string& path);
		Scene& CreateScene();
		Scene* GetScene(int index) const;

		void Update();
		void Render();

	private:
		friend class Minigin;
		SceneManager();

		std::vector<std::unique_ptr<Scene>> m_scenes{};
		std::unique_ptr<PrefabFactory> m_PrefabFactory;
	};
}
