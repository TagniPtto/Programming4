#pragma once

#include <Components/ObjectComponent.h>

namespace pengo {
	class GridInteractionComponent : public dae::ObjectComponent {
	public:
		virtual ~GridInteractionComponent() = default;
		explicit GridInteractionComponent(dae::GameObject& owner);

		void Deserialize(const nlohmann::json& data) override;
		void Serialize(nlohmann::json&) const override;

		void RequestPush();

	};
}
