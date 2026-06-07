#pragma once
#include "glm/vec2.hpp"

#include "Components/ObjectComponent.h"
#include <memory>

namespace pengo 
{
	class BlockComponent : public dae::ObjectComponent
	{
	public:
		explicit BlockComponent(dae::GameObject& owner);
		virtual void RenderUI();
		virtual void Update();
		virtual void FixedUpdate(float);
	};
}