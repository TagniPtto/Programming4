#include "GridComponent.h"
#include "BlockComponent.h"

#include <ServiceLocator.h>
#include <SceneSystem/SceneManager.h>
#include <Components/RenderComponent.h>

#include "imgui.h"

void pengo::GridComponent::Update()
{
}

void pengo::GridComponent::RenderUI()
{
	ImGui::Begin("GridObjectWindow", &m_debugWindowOpen);

	ImGui::End();
}

void pengo::GridComponent::Render() const
{
}

pengo::GridComponent::GridComponent(dae::GameObject& owner,int cellXCount, int cellYCount, int cellSize) :
	ObjectComponent(owner),
	m_cellXCount(cellXCount),
	m_cellYCount(cellYCount),
	m_cellSize(cellSize)

{
	dae::Scene* currentScene =  dae::ServiceLocator<dae::SceneManager>::Get().GetScene(0);
	if (!currentScene) return;
	for (int x{}; x < m_cellXCount; ++x)
	{
		for (int y{}; y < m_cellYCount; ++y)
		{
			auto obj = currentScene->CreateGameObject();
			obj->SetParent(m_owner);
			obj->GetTransform()->SetLocalPosition(float(x * m_cellSize),float(y * m_cellSize));
			obj->AddComponent<pengo::BlockComponent>();
			obj->AddComponent<dae::RenderComponent>("IceCube.png");

		}
	}
}
