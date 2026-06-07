#pragma once
#include <SDL3/SDL.h>

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final
	{

		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};	

	private:
		friend class Minigin;
		Renderer() = default;

	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture,
			const float srcX,
			const float srcY,
			const float srcWidth,
			const float srcHeight,
			const float dstX,
			const float dstY,
			const float dstWidth,
			const float dstHeight,
			const float angle = 0) const;
		void RenderTexture(const Texture2D& texture,
			const float dstX,
			const float dstY,
			const float dstWidth,
			const float dstHeight,
			const float angle = 0) const;

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
	};
}

