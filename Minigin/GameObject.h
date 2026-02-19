#pragma once
#include <string>
#include <memory>
#include <vector>

#include "Transform.h"
#include "ObjectComponent.h"

namespace dae
{
	class Texture2D;
	class GameObject final
	{
		Transform m_transform{};

		std::vector<ObjectComponent*> m_components{};
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


		template<typename T, typename... Args>
		typename std::enable_if<std::is_base_of<ObjectComponent, T>::value, void>::type AddComponent(Args&&... args);

		template<typename T>
		typename std::enable_if<std::is_base_of<ObjectComponent, T>::value, T*>::type GetComponent();

		template<typename T>
		typename std::enable_if<std::is_base_of<ObjectComponent, T>::value, void>::type RemoveComponent();

		template<typename T>
		typename std::enable_if<std::is_base_of<ObjectComponent, T>::value, bool>::type HasComponent();
	};
	template <typename T, typename... Args>
	inline typename std::enable_if<std::is_base_of<ObjectComponent, T>::value, void>::type GameObject::AddComponent(Args&&... args)
	{
		m_components.emplace_back(new T(*this, std::forward<Args>(args)...));  // Create unique_ptr to T, not ObjectComponent
	}

	template<typename T>
	inline typename std::enable_if<std::is_base_of<ObjectComponent, T>::value, T* >::type GameObject::GetComponent()
	{
		for (auto& component : m_components) {
			if (typeid(*component) == typeid(T))
			{
				return dynamic_cast<T*>(component);
			}
		}
		return nullptr;
	}
	template<typename T>
	inline typename std::enable_if<std::is_base_of<ObjectComponent, T>::value, void>::type GameObject::RemoveComponent()
	{
		for (auto& component : m_components) {
			if (typeid(*component) == typeid(T)) {
				delete *component;
				m_components.erase(component);
			}
		}
	}
	
	template<typename T>
	inline typename std::enable_if<std::is_base_of<ObjectComponent, T>::value, bool>::type GameObject::HasComponent()
	{
		for (const auto& component : m_components) {
			if (typeid(*component) == typeid(T))return true;
		}
		return false;
	}
}
