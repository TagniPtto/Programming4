#pragma once
#include <string>
#include <memory>
#include <SDL3/SDL.h>

#include "ObjectComponent.h"
#include "Transform.h"

namespace dae
{
	class Font;
	class Texture2D;
	class RenderComponent;
	class TextComponent : public ObjectComponent
	{
		RenderComponent* m_renderComponent{};
	public:
		void Update() override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);
		void SetColor(const SDL_Color& color);
		void SetFont(std::shared_ptr<Font> font);

		TextComponent(GameObject& owner , const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color = { 255, 255, 255, 255 });
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	private:
		bool m_needsUpdate{};
		std::string m_text{};
		SDL_Color m_color{ 255, 255, 255, 255 };
		Transform m_transform{};
		std::shared_ptr<Font> m_font{};
		RenderComponent* renderComponent;
	};
}
