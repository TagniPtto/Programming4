#include "RenderComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"


#include "../ServiceLocator.h"
#include "../ResourceSystem/ResourceManager.h"
#include "../Renderer.h"


#include <chrono>
namespace dae {
	void RenderComponent::SetSourceRectangle(float x, float y, float width, float height)
	{
		m_srcRectangle.x = x;
		m_srcRectangle.y = y;
		m_srcRectangle.width = width;
		m_srcRectangle.height = height;
	}

	void RenderComponent::SetDestinationRectangle(float x, float y, float width, float height)
	{
		m_dstRectangle.x = x;
		m_dstRectangle.y = y;
		m_dstRectangle.width = width;
		m_dstRectangle.height = height;
	}

	void RenderComponent::SetSourceRectangle(Rect src)
	{
		m_srcRectangle = src;
	}

	void RenderComponent::SetDestinationRectangle(Rect dst)
	{
		m_dstRectangle = dst;
	}

	RenderComponent::RenderComponent(dae::GameObject& owner, const std::string& filename) :
		ObjectComponent(owner), 
		m_texture(nullptr)
	{
		if (filename.empty()) return;

		m_texture = ServiceLocator<ResourceManager>::Get().LoadTexture(filename);
		if (m_texture) {
			float width, height;
			SDL_GetTextureSize(m_texture->GetSDLTexture(), &width, &height);
			m_srcRectangle = { 0,0,width,height };
			m_dstRectangle = { 0,0,width,height };
		}

	}


	void RenderComponent::Render() const
	{
		auto transform = m_owner->GetTransform();

		if (m_texture != nullptr) {
			auto worldPos = transform->GetWorldPosition();
			auto worldRot = transform->GetWorldRotation();
			ServiceLocator<Renderer>::Get().RenderTexture(
				*m_texture, 
				m_srcRectangle.x,
				m_srcRectangle.y,
				m_srcRectangle.width,
				m_srcRectangle.height,

				m_dstRectangle.x + worldPos.x,
				m_dstRectangle.y + worldPos.y,
				m_dstRectangle.width,
				m_dstRectangle.height,

				worldRot);
		}
	}

	void RenderComponent::SetTexture(const std::string& filename)
	{
		m_texture = dae::ServiceLocator<dae::ResourceManager>::Get().LoadTexture(filename);
	}
	void RenderComponent::SetTexture(std::shared_ptr<dae::Texture2D> texture)
	{
		m_texture = std::move(texture);
	}

	void RenderComponent::Deserialize(const nlohmann::json& data)
	{
		if (auto it = data.find("texture"); it != data.end()) {
			SetTexture(*it);
		}
		if (auto it = data.find("destinationRect"); it != data.end()) {
			auto dstR = *it;
			SetDestinationRectangle({ dstR[0],dstR[1],dstR[2],dstR[3] });
		}
	}

	void RenderComponent::Serialize(nlohmann::json&)
	{}

}
