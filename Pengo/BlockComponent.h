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
		virtual void RenderUI()override;
		virtual void Update()override;
		virtual void FixedUpdate(float)override;


		virtual void Deserialize(const nlohmann::json& data) override;
		virtual void Serialize(nlohmann::json& data) const override;
	};
}