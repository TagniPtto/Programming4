#pragma once
#include <string>
#include <memory>
#include <SDL3/SDL.h>

#include "ObjectComponent.h"

namespace dae
{
	class Font;
	class Texture2D;
	class RenderComponent;
	class TextComponent : public ObjectComponent
	{
	public:
		void Update() override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetColor(const SDL_Color& color);
		void SetFont(std::shared_ptr<Font> font);
		
		void Deserialize(const nlohmann::json& data)override;
		void Serialize(nlohmann::json& data) const override;

	public:
		TextComponent(GameObject& owner, const std::string& text = "", std::shared_ptr<Font> font = {}, const SDL_Color& color = { 255, 255, 255, 255 });
		virtual ~TextComponent() = default;

	private:
		bool m_needsUpdate{};
		std::string m_text{};
		SDL_Color m_color{ 255, 255, 255, 255 };
		std::shared_ptr<Font> m_font{};
		RenderComponent* renderComponent;
	};
}
