#pragma once

#include <Components/ObjectComponent.h>
#include <vector>

namespace dae {

	struct Rect {
		int left,top;
		int width, height;
	};
	class AnimationSequence final{
	public:
		enum class AnimationPlayBack {
			Normal,
			Looped,
			Reversed,
			ReverseLooped,
		};
	private:
		Rect m_startingFrame;
		AnimationPlayBack m_playback;
		
		float m_timer;
		float m_timePerFrame;
		
		int m_currentIndex;
		int m_sequenceLength;
	public:
		void Update(float deltaTime);
		Rect Get() const;
		AnimationSequence() = default;
	};

	class RenderComponent;
	class AnimationComponent : public ObjectComponent {

	public:
		AnimationComponent(dae::GameObject& owner);
		~AnimationComponent();
		virtual void Update() override;
		virtual void Render() const override;

	private:
		std::vector<AnimationSequence> m_sequences;
		RenderComponent* m_pRenderComponent{};
	};

}