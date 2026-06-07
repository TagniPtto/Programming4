#pragma once

#include <Components/ObjectComponent.h>
#include <vector>
#include <string>

namespace dae {

	struct Rect {
		float left,top;
		float width, height;
	};
	class AnimationSequence final{
	public:
		enum struct AnimationPlayBack {
			Normal,
			Looped,
			Reversed,
			ReverseLooped,
		};

	private:
		Rect m_SourceRectangle;
		int m_rows;
		int m_columns;

		int m_sequenceStart;
		int m_sequenceLength;

		AnimationPlayBack m_playback;
		
		float m_timer;
		float m_timePerFrame;
		
		int m_currentIndex;
	public:
		void Update(float deltaTime);
		void Reset();

		Rect Get() const;
		AnimationSequence(const Rect& sourceRect, int columns, int rows, int sequenceStart, int sequenceLength, float timePerFrame, AnimationPlayBack playback = AnimationPlayBack::Normal);
		AnimationSequence(int columns, int rows, int sequenceStart, int sequenceLength, float timePerFrame, AnimationPlayBack playback = AnimationPlayBack::Normal);
	};

	class RenderComponent;
	class AnimationComponent : public ObjectComponent {

	public:
		explicit AnimationComponent(dae::GameObject& owner , const std::string& fPath);
		~AnimationComponent();
		virtual void Update() override;
		virtual void Render() const override;

		virtual void AddAnimationSequence(const Rect& sourceRect, int rows, int columns, int sequenceStart, int sequenceLength, float timePerFrame, AnimationSequence::AnimationPlayBack playback = AnimationSequence::AnimationPlayBack::Normal);
		virtual void AddAnimationSequence(AnimationSequence animSeq);
	private:
		int m_currentSequence;
		std::vector<AnimationSequence> m_sequences;
		RenderComponent* m_pRenderComponent{};
	};

}