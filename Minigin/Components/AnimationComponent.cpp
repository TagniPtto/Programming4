#include "AnimationComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "TimeManager.h"

#include <iostream>
dae::AnimationComponent::AnimationComponent(dae::GameObject& owner):
	ObjectComponent(owner)
{
	m_pRenderComponent = owner.GetComponent<RenderComponent>();
	if (m_pRenderComponent) {

	}
	else {
		m_pRenderComponent = owner.AddComponent<RenderComponent>("PengoCharacterSprites.png");
	}
}

dae::AnimationComponent::~AnimationComponent() = default;

void dae::AnimationComponent::Update()
{
	float deltaTime = Time::GetInstance().GetDeltaTime();
	for (auto& sequence : m_sequences) {
		sequence.Update(deltaTime);
	}
}

void dae::AnimationComponent::Render() const
{
	std::cout << "Render AnimationComponent\n";
}

void dae::AnimationSequence::Update(float deltaTime)
{
	m_timer += deltaTime;
	if (m_timer >= m_timePerFrame) {
		m_timer = 0.f;
		switch (m_playback) {
		case AnimationPlayBack::Normal:
		case AnimationPlayBack::Reversed:
			if (m_currentIndex == m_sequenceLength - 1) return;
			++m_currentIndex;
			break;
		case AnimationPlayBack::Looped:
		case AnimationPlayBack::ReverseLooped:
			m_currentIndex = (++m_currentIndex) % m_sequenceLength;
			break;
		}
	}
}

dae::Rect dae::AnimationSequence::Get() const
{
	int index;
	if (m_playback == AnimationPlayBack::Reversed || m_playback == AnimationPlayBack::ReverseLooped) {
		index = m_sequenceLength - m_currentIndex;
	}
	else {
		index = m_currentIndex;
	}
	Rect result{ 
		.left = m_startingFrame.left + index * m_startingFrame.width,
		.top = m_startingFrame.top + index * m_startingFrame.height,
		.width = m_startingFrame.width,
		.height = m_startingFrame.height};
	return result;
}
