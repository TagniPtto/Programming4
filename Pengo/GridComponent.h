#pragma once
#include "Components/ObjectComponent.h"
#include <glm/glm.hpp>
#include <vector>
#include <cinttypes>
#include <string>

namespace pengo {
	enum class CellType : uint32_t {
		Empty,
		IceBlock,
		StandardBlock
	};
	
	struct GridCell {
		CellType type;
		dae::GameObject* occupant;
	};

	class GridComponent final : public dae::ObjectComponent
	{
	private:
		int m_cellXCount{};
		int m_cellYCount{};

		int m_cellSize{};
		std::vector<GridCell> m_cells;

		bool m_debugWindowOpen{true};

	public:

		void Update() override;
		void RenderUI() override;
		void Render() const override;
		
		int GetClosestCellId(glm::vec2);
		
		explicit GridComponent(dae::GameObject& owner , const std::string& path);

		void LoadMap(const std::string& path);

		~GridComponent() = default;

		GridComponent(const GridComponent& other) = delete;
		GridComponent(GridComponent&& other) = delete;
		GridComponent& operator=(const GridComponent& other) = delete;
		GridComponent& operator=(GridComponent&& other) = delete;

	};
}
