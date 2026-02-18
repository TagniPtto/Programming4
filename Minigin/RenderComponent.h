#pragma once
#include "ObjectComponent.h"
#include "Texture2D.h"
#include <memory>

class RenderComponent : public ObjectComponent
{
private:
	std::shared_ptr<dae::Texture2D> m_texture;
public:
	RenderComponent(dae::GameObject& owner);
	void Render() const override;
	void SetTexture(const std::string& filename);
};

