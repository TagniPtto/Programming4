#pragma once
#include "Components/ObjectComponent.h"
#include <vector>

namespace pengo {
	class GridComponent final : public dae::ObjectComponent
	{
	private:
		int m_cellXCount{};
		int m_cellYCount{};

		int m_cellSize{};

		bool m_debugWindowOpen{true};
	public:

		void Update() override;
		void RenderUI() override;
		void Render() const override;

		explicit GridComponent(dae::GameObject& owner , int cellXCount, int cellYCount, int cellsize);
		~GridComponent() = default;

		GridComponent(const GridComponent& other) = delete;
		GridComponent(GridComponent&& other) = delete;
		GridComponent& operator=(const GridComponent& other) = delete;
		GridComponent& operator=(GridComponent&& other) = delete;

	};
}
