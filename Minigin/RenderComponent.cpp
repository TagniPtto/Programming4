#include "RenderComponent.h"
#include "GameObject.h"

#include "ResourceManager.h"
#include "Renderer.h"

RenderComponent::RenderComponent(dae::GameObject& owner): 
	ObjectComponent(owner)
{
}

void RenderComponent::Render() const
{
	//const auto& pos = m_owner->GetWorldPosition();
	//if (m_texture != nullptr) {
	//	dae::Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
	//}
}

void RenderComponent::SetTexture(const std::string& filename)
{
	m_texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}
