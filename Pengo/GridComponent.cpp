#include "GridComponent.h"


pengo::GridComponent::GridComponent(dae::GameObject& owner,int cellXCount, int cellYCount, int cellsize) :
	ObjectComponent(owner),
	m_cellXCount(cellXCount),
	m_cellYCount(cellYCount),
	m_cellSize(cellsize)

{
}
