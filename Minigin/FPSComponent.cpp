#include "FPSComponent.h"
#include "GameObject.h"
#include <iomanip>
#include <sstream>
dae::FPSComponent::FPSComponent(GameObject& owner,const std::string& text, std::shared_ptr<Font> font) :
	ObjectComponent(owner), timeCounter(0), frameCount(0)
{
	if (!m_owner->HasComponent<TextComponent>()) {
		throw std::runtime_error("Cant have an FPS component without a TextComponent");
	}
	m_textRenderer = m_owner->GetComponent<TextComponent>();
	m_textRenderer->SetText(text);
}
void dae::FPSComponent::Update(float deltaTime)
{
	timeCounter += deltaTime;
	frameCount++;
	if (timeCounter > 1.0f) {
		float fps = (float(frameCount) / timeCounter) * 1.0f;
		std::ostringstream oss;
		oss << std::fixed << std::setprecision(1) << "FPS: " << fps;
		// Get the formatted string
		std::string formatted_fps = oss.str();
		
		m_textRenderer->SetText(formatted_fps);
		timeCounter -= 1;
		frameCount = 0;
	}
	m_textRenderer->Update(deltaTime);
}
void dae::FPSComponent::Render() const
{
	m_textRenderer->Render();
}