#include "RotationComponent.h"

#include "GameObject.h"
#include "TimeManager.h"

dae::RotationComponent::RotationComponent(GameObject& owner, float frequency):
	ObjectComponent(owner), m_frequency(frequency)
{
}

void dae::RotationComponent::Update()
{
	m_currentAngle += m_frequency * Time::GetInstance().GetDeltaTime();
	m_owner->SetLocalRotation(m_currentAngle);
}
