#include "GridComponent.h"
#include "BlockComponent.h"

#include <ServiceLocator.h>
#include <SceneSystem/SceneManager.h>
#include <SceneSystem/Scene.h>
#include <Components/RenderComponent.h>
#include <Renderer.h>
#include <LoggingSystem/Logger.h>

#include "imgui.h"


#include <nlohmann/json.hpp>
#include <fstream>


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
	auto renderer = dae::ServiceLocator<dae::Renderer>::Get();

	for (auto& cell: m_cells) {
		cell;
	}
}

int pengo::GridComponent::GetClosestCellId(glm::vec2 position)
{
	int cellX  = int(position.x  / m_cellSize);
	int cellY  = int(position.y  / m_cellSize);

	cellX  = std::max(0,std::min(m_cellXCount,cellX));
	cellY  = std::max(0,std::min(m_cellYCount,cellY));
	
	return cellX + cellY * m_cellXCount;
}



pengo::GridComponent::GridComponent(dae::GameObject& owner, const std::string& path):
	ObjectComponent(owner),
	m_cellXCount(),
	m_cellYCount(),
	m_cellSize(),
	m_cells()
{
	LoadMap(path);
}

void pengo::GridComponent::LoadMap(const std::string& path)
{
	dae::Scene* currentScene = dae::ServiceLocator<dae::SceneManager>::Get().GetScene(0);
	dae::Logger& logger = dae::ServiceLocator<dae::Logger>::Get();
	if (!currentScene) return;

	std::ifstream file(path);
	auto data = nlohmann::json::parse(file);

	m_cellSize = data["tileSize"];
	m_cellXCount = data["width"];
	m_cellYCount = data["height"];

	auto tiles = data["tiles"];

	for (int y = 0; y < m_cellYCount; y++)
	{
		for (int x = 0; x < m_cellXCount; x++)
		{
			int tile = tiles[y][x];

			if (tile == 1)
			{
				auto obj = currentScene->CreateGameObject();
				obj->SetParent(m_owner);
				float xPos{ float(x * m_cellSize) };
				float yPos{ float(y * m_cellSize) };
				obj->GetTransform()->SetLocalPosition(xPos, yPos);
				obj->AddComponent<pengo::BlockComponent>();
				auto renderComp = obj->AddComponent<dae::RenderComponent>("IceCube.png");
				dae::RenderComponent::Rect rect{ float(0) , float(0) , float(m_cellSize),float(m_cellSize) };
				renderComp->SetDestinationRectangle(rect);
				logger.Write("[" + std::to_string(xPos)  + "," + std::to_string(yPos) + "]");
			}
			else
			{
				// empty
			}
		}
	}
}
