#pragma once
#include "ObjectComponent.h"
#include "Texture2D.h"
#include <memory>


namespace dae {
	class RenderComponent : public ObjectComponent
	{
	private:
		std::shared_ptr<dae::Texture2D> m_texture;
	public:
		RenderComponent(dae::GameObject& owner, const std::string& filename);
		RenderComponent(dae::GameObject& owner);
		void Render() const override;
		void SetTexture(const std::string& filename);
		void SetTexture(std::shared_ptr<dae::Texture2D> texture);
	};


}
