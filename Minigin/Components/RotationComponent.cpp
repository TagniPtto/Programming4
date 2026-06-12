#include "RotationComponent.h"
#include "TransformComponent.h"

#include "GameObject.h"
#include "TimeManager.h"

dae::RotationComponent::RotationComponent(GameObject& owner, float frequency):
	ObjectComponent(owner), m_frequency(frequency)
{
	
}

void dae::RotationComponent::Deserialize(const nlohmann::json&)
{}

void dae::RotationComponent::Serialize(nlohmann::json &) const
{}

void dae::RotationComponent::Update()
{
	m_currentAngle += m_frequency * Time::Get().GetDeltaTime();
	m_owner->GetTransform()->SetLocalRotation(m_currentAngle);
}
