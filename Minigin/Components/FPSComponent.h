
#pragma once
#include "TextComponent.h"

namespace dae {

    class TextComponent;
	class GameObject;
    class FPSComponent : public ObjectComponent
    {
    public:
        FPSComponent(GameObject& owner, const std::string& text = "", std::shared_ptr<Font> font = {});

        void Deserialize(const nlohmann::json& data)override;
        void Serialize(nlohmann::json& data)const override;

        void Update() override;
    private:
        float timeCounter;
        int frameCount;

        TextComponent* textComponent;
    };
}