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
		Transform m_transform{};

		std::vector<std::unique_ptr<ObjectComponent>> m_components{};



	public:
		void Update(float deltaTime);
		void Render() const;

		void SetPosition(float x, float y);
		const glm::vec3& GetPosition() const;

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	
		template<Component T,typename... Args>
		void AddComponent(Args&&... args) {
			m_components.emplace_back(new T(*this, std::forward<Args>(args)...));
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
