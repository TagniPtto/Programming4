#include "FPSComponent.h"
#include "GameObject.h"
#include <iomanip>
#include <sstream>
#include "TimeManager.h"
dae::FPSComponent::FPSComponent(GameObject& owner, const std::string& text, std::shared_ptr<Font> font) :
	ObjectComponent(owner), timeCounter(0), frameCount(0)
{
	textComponent = owner.GetComponent<TextComponent>();
	if (textComponent) {
		textComponent->SetFont(font);
		textComponent->SetText(text);
	}
	else {
		textComponent = owner.AddComponent<TextComponent>(text, font);
	}

}
void dae::FPSComponent::Deserialize(const nlohmann::json& data)
{
	textComponent->Deserialize(data);
}
void dae::FPSComponent::Serialize(nlohmann::json &) const
{}

void dae::FPSComponent::Update()
{
	timeCounter += Time::Get().GetDeltaTime();
	frameCount++;
	if (timeCounter > 1.0f) {
		float fps = float(frameCount) / timeCounter;
		//std::ostringstream oss;
		//oss << std::fixed << std::setprecision(1) << "FPS: " << fps;
		//// Get the formatted string
		//std::string formatted_fps = oss.str();

		std::string formatted_fps = std::format("FPS : {:.0f}", fps);
		
		textComponent->SetText(formatted_fps);
		timeCounter = 0;
		frameCount = 0;
	}
}