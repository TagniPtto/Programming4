#pragma once
#include <string>
#include <memory>
#include <vector>

#include "Transform.h"
#include "ObjectComponent.h"

namespace dae
{

	template<typename T>
	concept Component = std::derived_from<T, ObjectComponent>;

	class Texture2D;
	class GameObject final
	{
		Transform m_localtransform{};
		Transform m_worldTransform{};

		std::vector<std::unique_ptr<ObjectComponent>> m_components{};
		bool m_markedForDestruction{ false };

		GameObject* m_parent{ nullptr };
		std::vector<GameObject*> m_children{};

		bool m_transformDirty{ false };
	private:
		void RemoveChild(GameObject* child);
		void AddChild(GameObject* child);
		bool IsChildOf(GameObject* potentialParent);

	public:
		void Update();
		void Render() const;

		GameObject* GetParent() const;
		void SetParent(GameObject* newParent, bool keepWorldPosition = false);

		void SetLocalPosition(float x, float y);
		void SetLocalPosition(glm::vec3 pos);
		
		void SetLocalRotation(float newRotation);

		void SetLocalTransform(const Transform& newTransform);

		glm::vec3 GetWorldPosition();
		float GetWorldRotation();
		Transform GetWorldTransform();

		void UpdateWorldTransform();

		void MarkForDestruction();
		bool IsMarkedForDestruction() const;
		void SetTransformDirty();

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	
		template<Component T,typename... Args>
		T* AddComponent(Args&&... args) {
			m_components.emplace_back(new T(*this, std::forward<Args>(args)...));
			return dynamic_cast<T*>(m_components.back().get());
		}

		template<Component T>
		std::vector<T*> GetComponents()
		{
			std::vector<T*> result;

			for (auto& comp : m_components)
			{
				if (auto casted = dynamic_cast<T*>(comp.get()))
					result.push_back(casted);
			}

			return result;
		}
		template<Component T>
		T* GetComponent()
		{
			for (const auto& component : m_components)
			{
				if (auto casted = dynamic_cast<T*>(component.get()))
					return casted;
			}

			return nullptr;

		}

		template<Component T>
		void RemoveComponent() {
			m_components.erase(std::remove_if(m_components.begin(), m_components.end(), [](const std::unique_ptr<T>& component) { dynamic_cast<T*>(component.get()) != nullptr; }), m_components.end());
		}

		template<Component T>
		bool HasComponent() {
			return std::find_if(m_components.begin(), m_components.end(), [](const std::unique_ptr<T>& component) { dynamic_cast<T*>(component.get()) != nullptr; }) != m_components.end();
		
		}
	};
}
