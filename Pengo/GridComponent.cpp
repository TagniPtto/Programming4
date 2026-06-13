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


#include <imgui.h>
#include <nlohmann/json.hpp>
#include <fstream>

#define ORIGINAL_PIXEL_COUNT_BORDER 8
#define ORIGINAL_PIXEL_COUNT_BlOCK 16

bool pengo::GridComponent::IsValidTileIndex(glm::ivec2 index)
{
	return !(index.x > m_tileXCount || index.x < 0 || index.y > m_tileYCount || index.y < 0);
}

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
	//auto renderer = dae::ServiceLocator<dae::Renderer>::Get();

	//for (auto& rows: m_tiles) {
	//	for (auto& tile : rows) {

	//	}
	//}
}


glm::ivec2 pengo::GridComponent::GetClosestAvailableTile(glm::vec3 position)
{
	int tileX = int(position.x / m_tileSize);
	int tileY = int(position.y / m_tileSize);

	tileX = std::max(0, std::min(m_tileXCount, tileX));
	tileY = std::max(0, std::min(m_tileYCount, tileY));


	for (int y{ -1 }; y < 1; y++) {
		for (int x{ -1 }; x < 1; x++) {

			glm::ivec2 tileId(
				std::max(0, std::min(m_tileXCount, tileX + x)),
				std::max(0, std::min(m_tileYCount, tileY + y)));

			if (!IsTileOccupiedByBlock(tileId)) {
				return tileId;
			}
		}
	}

	return glm::ivec2(tileX, tileY);
}

glm::vec3 pengo::GridComponent::GetTilePosition(glm::vec2 posId) const
{
	return m_owner->GetTransform()->GetWorldPosition() + glm::vec3(posId.x *m_tileSize, posId.y * m_tileSize,0.0f);
}

bool pengo::GridComponent::IsTileOccupiedByBlock(glm::ivec2 posId)
{
	if (!IsValidTileIndex(posId)) return true;
	return m_blocks[posId.y][posId.x].occupant;
}

void pengo::GridComponent::ReserveTile(glm::ivec2)
{

}



pengo::GridComponent::GridComponent(dae::GameObject& owner, const std::string& path):
	ObjectComponent(owner),
	m_tileXCount(),
	m_tileYCount(),
	m_tileSize()
{
	std::ifstream file(path);
	if (file.is_open()) {
		auto data = nlohmann::json::parse(file);
		LoadMap(path);
	}
}

void pengo::GridComponent::LoadMap(const nlohmann::json& data)
{
	dae::Scene* currentScene = dae::ServiceLocator<dae::SceneManager>::Get().GetActiveScene();
	if (!currentScene) return;

	m_tileSize = data["tileSize"];
	m_tileXCount = data["width"];
	m_tileYCount = data["height"];

	auto tiles = data["tiles"];
	m_tiles = std::vector<std::vector<Tile>>(m_tileYCount, std::vector<Tile>(m_tileXCount));
	m_blocks = std::vector<std::vector<Tile>>(m_tileYCount, std::vector<Tile>(m_tileXCount));

	for (int y = 0; y < m_tileYCount; y++)
	{
		for (int x = 0; x < m_tileXCount; x++)
		{
			if (tiles[y][x] == 1)
			{
				float xPos{ float(x * m_tileSize) };
				float yPos{ float(y * m_tileSize) };
				dae::GameObject* obj = dae::PrefabFactory::Get().Instantiate(*currentScene,"IceBlock",glm::vec3(xPos,yPos,0));
				obj->SetParent(m_owner);
				if (auto animComp = obj->GetComponent<dae::AnimationComponent>(); animComp) {
					animComp->SetAnimation("Idle");
				}
				if (auto renderComp = obj->GetComponent<dae::RenderComponent>(); renderComp) {
					renderComp->SetDestinationRectangle(0.0f,0.0f,float(m_tileSize),float(m_tileSize));
				}
				m_blocks[y][x].occupant = obj;
			}
			else
			{
				// empty
			}
		}
	}

	const float scale{ m_tileSize / float(ORIGINAL_PIXEL_COUNT_BlOCK) };
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

void pengo::GridComponent::Deserialize(const nlohmann::json& data)
{
	LoadMap(data);
}

void pengo::GridComponent::Serialize(nlohmann::json&) const
{}
