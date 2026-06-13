
#include <stdexcept>

#include <SDL3_ttf/SDL_ttf.h>

#include "TextComponent.h"
#include "RenderComponent.h"
#include "../ServiceLocator.h"
#include "Renderer.h"
#include "ResourceSystem/ResourceManager.h"
#include "ResourceSystem/Font.h"
#include "ResourceSystem/Texture2D.h"
#include "GameObject.h"


dae::TextComponent::TextComponent(dae::GameObject& owner ,const std::string & text, std::shared_ptr<Font> font, const SDL_Color & color)
	:ObjectComponent(owner), m_needsUpdate(true), m_text(text), m_color(color), m_font(std::move(font))
{
	renderComponent = owner.GetComponent<RenderComponent>();
	if (renderComponent == nullptr) {
		renderComponent = owner.AddComponent<RenderComponent>();
	}
}

void dae::TextComponent::Update()
{
	if (m_needsUpdate && renderComponent && !m_text.empty())
	{
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), m_text.length(), m_color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(ServiceLocator<Renderer>::Get().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_DestroySurface(surf);
		renderComponent->SetDestinationRectangle(0.0f,0.0f,float(texture->w), float(texture->h));
		renderComponent->SetSourceRectangle(0.0f,0.0f,float(texture->w), float(texture->h));
		renderComponent->SetTexture(std::make_shared<Texture2D>(texture));
		m_needsUpdate = false;
	}
}

void dae::TextComponent::Render() const
{
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_text = text;
	m_needsUpdate = true;
}


void dae::TextComponent::SetColor(const SDL_Color& color)
{
	m_color = color;
	m_needsUpdate = true;
}

void dae::TextComponent::SetFont(std::shared_ptr<Font> font)
{
	m_font = font;
}

void dae::TextComponent::Deserialize(const nlohmann::json& data)
{
	auto RM = ServiceLocator<ResourceManager>::Get();
	
	int fontSize = { 30 };
	if (auto it = data.find("fontSize"); it != data.end()) {
		fontSize = *it;
	}
	if (auto it = data.find("font"); it != data.end()) {

		SetFont(RM.LoadFont(*it,uint8_t(fontSize)));
	}
	if (auto it = data.find("fontColor"); it != data.end()) {
		auto FC = *it;
		SDL_Color color{ FC[0],FC[1],FC[2], 1 };
		SetColor(color);
	}
}

void dae::TextComponent::Serialize(nlohmann::json&) const
{}
