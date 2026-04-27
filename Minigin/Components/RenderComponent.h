#pragma once
#include "ObjectComponent.h"
#include "Texture2D.h"
#include <memory>


namespace dae {
	class RenderComponent : public ObjectComponent
	{
	private:
		std::shared_ptr<dae::Texture2D> m_texture;
		float m_scale{ 1.0f };

		int m_sourceX , m_sourceY , m_sourceWidth , m_sourceHeight;

	public:
		void SetSourceRectangle(int x , int y , int width, int height);
		void SetPivot(int x, int y);

		RenderComponent(dae::GameObject& owner, const std::string& filename , float scale = 1.0f);
		RenderComponent(dae::GameObject& owner);
		void Render() const override;
		void SetTexture(const std::string& filename);
		void SetTexture(std::shared_ptr<dae::Texture2D> texture);
	};


}
