#include "RenderComponent.h"
#include "GameObject.h"

#include "ResourceManager.h"
#include "Renderer.h"


namespace dae {
	RenderComponent::RenderComponent(dae::GameObject& owner, const std::string& filename , float scale) :
		ObjectComponent(owner), m_texture(dae::ResourceManager::GetInstance().LoadTexture(filename)), m_scale(scale)
	{
	}

	RenderComponent::RenderComponent(dae::GameObject& owner):
		ObjectComponent(owner), m_texture(nullptr)
	{
	}

	void RenderComponent::Render() const
	{
		const auto& transform = m_owner->GetWorldTransform();
		if (m_texture != nullptr) {
			dae::Renderer::GetInstance().RenderTexture(*m_texture, transform.GetPosition().x, transform.GetPosition().y, transform.GetRotation(),m_scale);
		}
	}

	void RenderComponent::SetTexture(const std::string& filename)
	{
		m_texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
	}
	void RenderComponent::SetTexture(std::shared_ptr<dae::Texture2D> texture)
	{
		m_texture = std::move(texture);
	}

}
