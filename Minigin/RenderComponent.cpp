#include "RenderComponent.h"
#include "GameObject.h"

#include "ResourceManager.h"
#include "Renderer.h"

RenderComponent::RenderComponent(dae::GameObject& owner, const std::string& filename):
	ObjectComponent(owner), m_texture(dae::ResourceManager::GetInstance().LoadTexture(filename))
{
}

void RenderComponent::Render() const
{
	const auto& pos = m_owner->GetPosition();
	if (m_texture != nullptr) {
		dae::Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
	}
}

void RenderComponent::SetTexture(const std::string& filename)
{
	m_texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}
