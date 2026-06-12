#pragma once
#include <memory>
#include <string>
#include <vector>
#include "../GameObject.h"

namespace dae
{
	class ObjectComponent;

	class Scene final
	{
	public:
		GameObject* CreateGameObject();
	

		void Add(std::unique_ptr<GameObject> object);
		void Remove(const GameObject& object);
		void RemoveAll();
		void DestroyMarkedObjects();

		void Update();
		void Render() const;
		void RenderUI();

		~Scene() = default;
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		template<Component T>
		T* FindComponent() const {
			for (auto& object : m_objects) {
				if (auto comp = object->GetComponent<T>(); comp) {
					return comp;
				}
			}
			return nullptr;
		}
	private:
		friend class SceneManager;
		explicit Scene() = default;

		std::vector<std::unique_ptr<GameObject>> m_objects{};
	};

}
