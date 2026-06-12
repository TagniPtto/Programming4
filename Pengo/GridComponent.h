#pragma once
#include "Components/ObjectComponent.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include <cinttypes>
#include <string>

namespace pengo {
	struct Tile {
		dae::GameObject* occupant;
		glm::ivec2 posId;
	};
	class GridComponent final : public dae::ObjectComponent
	{
	private:
		int m_tileXCount{};
		int m_tileYCount{};

		int m_tileSize{};

		std::vector<std::vector<Tile>> m_tiles;
		std::vector<std::vector<Tile>> m_blocks;

		bool m_debugWindowOpen{true};
	public:
		~GridComponent() = default;
		explicit GridComponent(dae::GameObject& owner, const std::string& path = "");

	private:
		bool IsValidTileIndex(glm::ivec2 index);


	public: 
		void Update() override;
		void RenderUI() override;
		void Render() const override;
		
		glm::ivec2 GetClosestAvailableTile(glm::vec3);
		glm::vec3 GetTilePosition(glm::vec2) const;
		bool IsTileOccupiedByBlock(glm::ivec2);
		void ReserveTile(glm::ivec2);




		void LoadMap(const nlohmann::json& data);
		void Deserialize(const nlohmann::json& data) override;
		void Serialize(nlohmann::json& data) const override;
	};
}
