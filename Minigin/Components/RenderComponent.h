#pragma once
#include "ObjectComponent.h"
#include "../ResourceSystem/Texture2D.h"
#include <memory>


namespace dae {

	class RenderComponent : public ObjectComponent
	{
	public:
		struct Rect {
			float x;
			float y;
			float width;
			float height;
		};
	private:
		std::shared_ptr<dae::Texture2D> m_texture;

		Rect m_srcRectangle{};
		Rect m_dstRectangle{};

	public:

		
		Rect GetSourceRectangle()const;
		Rect GetDesitionationRectangle()const;
		
		void SetSourceRectangle(float x , float y , float width, float height);
		void SetDestinationRectangle(float x , float y , float width, float height);
		void SetSourceRectangle(Rect src);
		void SetDestinationRectangle(Rect dst);



		RenderComponent(dae::GameObject& owner, const std::string& filename = "");

		void Render() const override;
		void SetTexture(const std::string& filename);
		void SetTexture(std::shared_ptr<dae::Texture2D> texture);

		virtual void Deserialize(const nlohmann::json& data)override;
		virtual void Serialize(nlohmann::json& data) const override;

	};


}
