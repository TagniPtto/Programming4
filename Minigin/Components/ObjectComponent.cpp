#include "ObjectComponent.h"
#include "GameObject.h"

namespace dae {
	ObjectComponent::ObjectComponent(dae::GameObject& owner) : m_owner(&owner)
	{
	}

}
