#include "GridInteractionComponent.h"

pengo::GridInteractionComponent::GridInteractionComponent(dae::GameObject& owner):
	dae::ObjectComponent(owner)
{}

void pengo::GridInteractionComponent::Deserialize(const nlohmann::json &)
{}

void pengo::GridInteractionComponent::Serialize(nlohmann::json&) const
{}

void pengo::GridInteractionComponent::RequestPush()
{}
