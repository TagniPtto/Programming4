#pragma once

#include <Components/ObjectComponent.h>
#include <map>
#include <string>

namespace dae {
	
	struct Rect {
		float left;
		float top;
		float width;
		float height;
	};
	class AnimationSequence final{
	public:
		enum struct AnimationPlayBack {
			Normal,
			Looped,
			Reversed,
			ReverseLooped,
		};
		bool m_playing = true;
	private:
		Rect m_SourceRectangle = {};
		int m_rows = 0;
		int m_columns = 0;

		int m_sequenceStart = 0;
		int m_sequenceLength = 0;

		AnimationPlayBack m_playback = AnimationPlayBack::Normal;
		
		float m_timer = 0;
		float m_timePerFrame = 0;
		
		int m_currentIndex = 0;


	public:
		AnimationSequence() = default;
		explicit AnimationSequence(const Rect& sourceRect, int columns, int rows, int sequenceStart, int sequenceLength, float timePerFrame, AnimationPlayBack playback = AnimationPlayBack::Normal);
		explicit AnimationSequence(int columns, int rows, int sequenceStart, int sequenceLength, float timePerFrame, AnimationPlayBack playback = AnimationPlayBack::Normal);
	public:
		void Update(float deltaTime);
		void Reset();

		Rect Get() const;
		void Deserialize(const nlohmann::json& data);
		void Serialize(nlohmann::json& data) const;
	
	};

	class RenderComponent;
	class AnimationComponent final : public ObjectComponent {

	public:
		explicit AnimationComponent(dae::GameObject& owner , const std::string& fPath = "");
		~AnimationComponent();
	public:
		void Update() override;
		void Render() const override;

		void PlayAnimation(const std::string& name);
		void PauseCurrentAnimation();
		void ResumeCurrentAnimation();
		
		void Deserialize(const nlohmann::json& data) override;
		void Serialize(nlohmann::json& data) const override;

		void AddAnimationSequence(std::string name,const Rect& sourceRect, int rows, int columns, int sequenceStart, int sequenceLength, float timePerFrame, AnimationSequence::AnimationPlayBack playback = AnimationSequence::AnimationPlayBack::Normal);
		void AddAnimationSequence(std::string name,AnimationSequence animSeq);
	private:
		AnimationSequence* m_currentSequence;
		std::unordered_map<std::string,AnimationSequence> m_sequences;
		RenderComponent* m_pRenderComponent{};
	};

}