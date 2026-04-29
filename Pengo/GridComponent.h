#pragma once
#include "Components/ObjectComponent.h"

class GridComponent final : public dae::ObjectComponent
{
public:
	GridComponent() = default;
	~GridComponent() = default;

	GridComponent(const GridComponent& other) = delete;
	GridComponent(GridComponent&& other) = delete;
	GridComponent& operator=(const GridComponent& other) = delete;
	GridComponent& operator=(GridComponent&& other) = delete;



	void Initialize();
};