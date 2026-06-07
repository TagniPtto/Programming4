#include <stdexcept>
#include <cstring>
#include <iostream>
#include "Renderer.h"


#include "ServiceLocator.h"
#include "SceneSystem/SceneManager.h"
#include "ResourceSystem/Texture2D.h"
#include "LoggingSystem/Logger.h"



#include <imgui.h>
#include <imgui_internal.h>

#include <imgui_plot.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>

#include <SDL3/SDL.h>

void dae::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
	m_renderer = SDL_CreateRenderer(window, nullptr);
	if (m_renderer == nullptr)
	{
		std::cout << "Failed to create the renderer: " << SDL_GetError() << "\n";
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;		 

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; 

#if __EMSCRIPTEN__
	io.IniFilename = NULL;
#endif

	ImGui_ImplSDL3_InitForSDLRenderer(window, m_renderer);
	ImGui_ImplSDLRenderer3_Init(m_renderer);
}


void dae::Renderer::Render() const
{
	ImGui_ImplSDLRenderer3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();

	ImGuiID dockspace_id = ImGui::GetID("My Dockspace");
	ImGuiViewport* viewport = ImGui::GetMainViewport();

	ImGui::DockSpaceOverViewport(dockspace_id, viewport, ImGuiDockNodeFlags_PassthruCentralNode);

	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	ServiceLocator<SceneManager>::Get().Render();
	ServiceLocator<Logger>::Get().RenderUI();

	ImGui::Render();
	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_renderer);
	SDL_RenderPresent(m_renderer);
}

void dae::Renderer::Destroy()
{
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();

	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, 
	const float srcX, 
	const float srcY, 
	const float srcWidth, 
	const float srcHeight, 
	const float dstX,
	const float dstY,
	const float dstWidth,
	const float dstHeight,
	const float angle) const
{
	SDL_FRect dst{};
	dst.x = dstX;
	dst.y = dstY;
	dst.w = dstWidth;
	dst.h = dstHeight;

	SDL_FRect src{};
	src.x = srcX;
	src.y = srcY;
	src.h = srcHeight;
	src.w = srcWidth;

	SDL_FPoint center{};
	center.x = 0;
	center.y = 0;

	SDL_RenderTextureRotated(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst, angle, &center, SDL_FLIP_NONE);
}

void dae::Renderer::RenderTexture(
	const Texture2D& texture, 
	const float dstX, 
	const float dstY, 
	const float dstWidth,
	const float dstHeight, 
	const float angle) const
{
	float width, height;
	SDL_GetTextureSize(texture.GetSDLTexture(), &width, &height);
	RenderTexture(texture,0,0,width,height,dstX,dstY,dstWidth,dstHeight,angle);
}



SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }
