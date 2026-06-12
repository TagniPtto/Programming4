#include "GridMovementComponent.h"
#include "GridComponent.h"
#include <GameObject.h>

#include <ServiceLocator.h>
#include <SceneSystem/SceneManager.h>
#include <SceneSystem/Scene.h>
#include <TimeManager.h>

pengo::GridMovementComponent::GridMovementComponent(dae::GameObject& owner, dae::TransformComponent* trans, GridComponent* grid):
	dae::ObjectComponent(owner),
    m_pTransformComp(trans), 
    m_pGridComp(grid)
{
    if (!m_pTransformComp) {
        m_pTransformComp = m_owner->GetTransform();
    }
    dae::Scene* scene = dae::ServiceLocator<dae::SceneManager>::Get().GetActiveScene();
    if (!m_pGridComp) {
        m_pGridComp = scene->FindComponent<pengo::GridComponent>();
    }
    if (m_pGridComp && m_pTransformComp) {
        glm::ivec2 posId = m_pGridComp->GetClosestAvailableTile(m_pTransformComp->GetWorldPosition());
        auto tilePos = m_pGridComp->GetTilePosition(posId);
        m_pTransformComp->SetLocalPosition(tilePos);
    }
}

bool pengo::GridMovementComponent::RequestMove( glm::ivec2 direction)
{
    if (m_IsMoving)
        return false;

    glm::ivec2 target = m_CurrentTile + direction;

    if (!m_pGridComp->IsTileOccupiedByBlock(target))
        return false;

    m_FromTile= m_CurrentTile;
    m_ToTile = target;

    m_Progress = 0.f;
    m_IsMoving = true;

    return true;
}

void pengo::GridMovementComponent::Update()
{
    if (!m_IsMoving)return;

    auto fromPosition = m_pGridComp->GetTilePosition(m_FromTile);
    auto toPosition = m_pGridComp->GetTilePosition(m_ToTile);
    auto direction = toPosition - fromPosition;

 
    auto position = m_pTransformComp->GetLocalPosition();
    auto newPosition = position + direction * dae::Time::Get().GetDeltaTime();
    if ((position - toPosition).length() < 1.0f) {
        m_IsMoving = false;
        m_pTransformComp->SetLocalPosition(toPosition);
    }
    else
    {
        m_pTransformComp->SetLocalPosition(newPosition);
    }
}

void pengo::GridMovementComponent::Deserialize(const nlohmann::json &)
{}

void pengo::GridMovementComponent::Serialize(nlohmann::json &) const
{}
