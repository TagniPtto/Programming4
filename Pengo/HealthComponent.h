#pragma once
 
#include "Components/ObjectComponent.h"

namespace Pengo {
	class GameObject;
	class HealthComponent : public dae::ObjectComponent {
		int m_health;
	public:
		explicit HealthComponent(dae::GameObject& owner, int health);
		~HealthComponent() = default;
		void TakeDamage(int damage);
		int GetHealth() const { return m_health; }
	};
}