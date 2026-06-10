#pragma once
 
#include "Components/ObjectComponent.h"

namespace pengo {
	class GameObject;
	class HealthComponent : public dae::ObjectComponent {
		int m_health;
	public:
		explicit HealthComponent(dae::GameObject& owner, int health = 10);
		~HealthComponent() = default;

		virtual void Deserialize(const nlohmann::json& data) override;
		virtual void Serialize(nlohmann::json& data) override;
	
	public:
		void TakeDamage(int damage);
		int GetHealth() const { return m_health; }
	};
}