#pragma once
#include <vector>
#include <string>
#include <memory>

namespace dae
{
	class Scene;
	class SceneManager final
	{
	public:
		~SceneManager();

		Scene& LoadScene(const std::string& path);
		Scene& CreateScene();

		Scene* GetScene(int index) const;
		Scene* GetActiveScene() const;

		void Update();
		void Render();

	private:
		friend class Minigin;
		SceneManager();

		int activeSceneIndex{};
		std::vector<std::unique_ptr<Scene>> m_scenes{};
	};
}
