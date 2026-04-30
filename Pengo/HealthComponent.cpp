#include "HealthComponent.h"
#include "GameObject.h"

dae::HealthComponent::HealthComponent(dae::GameObject& owner, int health) :
	dae::ObjectComponent(owner),
	m_health(health)
{
}

void dae::HealthComponent::TakeDamage(int damage)
{
	m_health -= damage;
	if (m_health <= 0) {
		m_owner->MarkForDestruction();
	}
}
