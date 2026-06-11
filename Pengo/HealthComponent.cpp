#include "HealthComponent.h"
#include "GameObject.h"

pengo::HealthComponent::HealthComponent(dae::GameObject& owner, int health) :
	dae::ObjectComponent(owner),
	m_health(health)
{
}

void pengo::HealthComponent::Deserialize(const nlohmann::json&)
{}

void pengo::HealthComponent::Serialize(nlohmann::json&) const
{}

void pengo::HealthComponent::TakeDamage(int damage)
{
	m_health -= damage;
	if (m_health <= 0) {
		m_owner->MarkForDestruction();
	}
}
