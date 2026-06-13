#include "GridInteractionComponent.h"
#include "GridComponent.h"

#include <ServiceLocator.h>
#include <SceneSystem/SceneManager.h>
#include <SceneSystem/Scene.h>

pengo::GridInteractionComponent::GridInteractionComponent(dae::GameObject& owner):
	dae::ObjectComponent(owner)
{
    dae::Scene* scene = dae::ServiceLocator<dae::SceneManager>::Get().GetActiveScene();
    if (!m_pGridComp) {
        m_pGridComp = scene->FindComponent<pengo::GridComponent>();
    }
}

void pengo::GridInteractionComponent::Deserialize(const nlohmann::json &)
{}

void pengo::GridInteractionComponent::Serialize(nlohmann::json&) const
{}

void pengo::GridInteractionComponent::RequestPush(glm::ivec2)
{}
