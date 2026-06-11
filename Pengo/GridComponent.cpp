#include "GridComponent.h"
#include "BlockComponent.h"

#include <ServiceLocator.h>
#include <SceneSystem/SceneManager.h>
#include <SceneSystem/Scene.h>
#include <Components/RenderComponent.h>
#include <Components/AnimationComponent.h>
#include <Renderer.h>
#include <LoggingSystem/Logger.h>
#include <SceneSystem/PrefabFactory.h>

#include "imgui.h"


#include <nlohmann/json.hpp>
#include <fstream>

#define ORIGINAL_PIXEL_COUNT_BORDER 8
#define ORIGINAL_PIXEL_COUNT_BlOCK 16

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
	std::ifstream file(path);
	if (file.is_open()) {
		auto data = nlohmann::json::parse(file);
		LoadMap(path);
	}
}

void pengo::GridComponent::LoadMap(const nlohmann::json& data)
{
	dae::Scene* currentScene = dae::ServiceLocator<dae::SceneManager>::Get().GetScene(0);
	if (!currentScene) return;

	m_cellSize = data["tileSize"];
	m_cellXCount = data["width"];
	m_cellYCount = data["height"];

	auto tiles = data["tiles"];

	for (int y = 0; y < m_cellYCount; y++)
	{
		for (int x = 0; x < m_cellXCount; x++)
		{
			if (tiles[y][x] == 1)
			{
				float xPos{ float(x * m_cellSize) };
				float yPos{ float(y * m_cellSize) };
				dae::GameObject* obj = dae::PrefabFactory::Get().Instantiate(currentScene,"IceBlock",glm::vec3(xPos,yPos,0));
				obj->SetParent(m_owner);
				if (auto animComp = obj->GetComponent<dae::AnimationComponent>(); animComp) {
					animComp->SetAnimation("Idle");
				}
				if (auto renderComp = obj->GetComponent<dae::RenderComponent>(); renderComp) {
					renderComp->SetDestinationRectangle(0.0f,0.0f,float(m_cellSize),float(m_cellSize));
				}
			}
			else
			{
				// empty
			}
		}
	}

	const float scale{ m_cellSize / float(ORIGINAL_PIXEL_COUNT_BlOCK) };
	const float offset{ float(ORIGINAL_PIXEL_COUNT_BORDER) * scale };

	if (auto renderComp = m_owner->GetComponent<dae::RenderComponent>(); renderComp) {

		auto srcRect = renderComp->GetSourceRectangle();
		renderComp->SetDestinationRectangle({
			srcRect.x - offset,
			srcRect.y - offset,
			srcRect.width * scale,
			srcRect.height * scale,
			});
	}
}

pengo::MoveResult pengo::GridComponent::TryMove(glm::ivec2 currentTile, glm::ivec2 direction)
{
	currentTile;
	direction;
	return MoveResult();
}

void pengo::GridComponent::Deserialize(const nlohmann::json& data)
{
	LoadMap(data);
}

void pengo::GridComponent::Serialize(nlohmann::json&) const
{}
