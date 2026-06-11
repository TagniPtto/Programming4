#include "BlockComponent.h"

pengo::BlockComponent::BlockComponent(dae::GameObject& owner):
	ObjectComponent(owner)
{
}

void pengo::BlockComponent::RenderUI()
{
}

void pengo::BlockComponent::Update()
{
}

void pengo::BlockComponent::FixedUpdate(float)
{
}

void pengo::BlockComponent::Deserialize(const nlohmann::json&)
{}

void pengo::BlockComponent::Serialize(nlohmann::json&) const
{}
