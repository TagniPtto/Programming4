#include <stdexcept>
#include <cstring>
#include <iostream>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"

void dae::Renderer::Init(SDL_Window* window)
{
	m_window = window;

	SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

#if defined(__EMSCRIPTEN__)
	m_renderer = SDL_CreateRenderer(window, nullptr);
#else
	m_renderer = SDL_CreateRenderer(window, nullptr);
#endif

	if (m_renderer == nullptr)
	{
		std::cout << "Failed to create the renderer: " << SDL_GetError() << "\n";
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();

	SDL_RenderPresent(m_renderer);
}

void dae::Renderer::Destroy()
{
	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height, float angle) const
{
	SDL_FRect dst{};
	dst.x = x;// - width * 0.5f;
	dst.y = y;// - height * 0.5f;
	dst.h = height;
	dst.w = width;

	SDL_FPoint center{};
	center.x = 0;//width * 0.5f;
	center.y = 0;//height * 0.5f;

	SDL_RenderTextureRotated(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, angle, &center, SDL_FLIP_NONE);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, float x, float y, float angle, float scale) const
{
	float width, height;
	SDL_GetTextureSize(texture.GetSDLTexture(), &width, &height);

	RenderTexture(texture, x, y, width * scale, height * scale, angle);	
}



SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }
