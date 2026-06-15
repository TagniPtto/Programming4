#include "ObjectComponent.h"
#include "GameObject.h"

namespace dae {
	ObjectComponent::ObjectComponent(dae::GameObject& owner) : m_owner(&owner)
	{}

	dae::GameObject* ObjectComponent::GetOwner() const
	{
		return m_owner;
	}

	void ObjectComponent::Render() const
	{}

	void ObjectComponent::RenderUI()
	{}

	void ObjectComponent::Update()
	{}

	void ObjectComponent::FixedUpdate(float)
	{}

	void ObjectComponent::Deserialize(const nlohmann::json&)
	{}

	void ObjectComponent::Serialize(nlohmann::json&) const
	{}

}
