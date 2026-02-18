#include "FPSComponent.h"
#include "GameObject.h"
#include <iomanip>
#include <sstream>
dae::FPSComponent::FPSComponent(GameObject& owner,const std::string& text, std::shared_ptr<Font> font) :
	TextComponent(owner,text,font), timeCounter(0), frameCount(0)
{
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
		
		SetText(formatted_fps);
		timeCounter -= 1;
		frameCount = 0;
	}
	TextComponent::Update(deltaTime);
}
void dae::FPSComponent::Render() const
{
	TextComponent::Render();
}