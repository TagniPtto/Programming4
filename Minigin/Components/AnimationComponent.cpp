#include "AnimationComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "TimeManager.h"

#include <iostream>



dae::AnimationComponent::AnimationComponent(dae::GameObject& owner, const std::string& fPath):
	dae::ObjectComponent(owner), m_currentSequence(0)
{
	m_pRenderComponent = owner.GetComponent<RenderComponent>();
	if (m_pRenderComponent) {
		m_pRenderComponent->SetTexture(fPath);
	}
	else {
		m_pRenderComponent = owner.AddComponent<RenderComponent>(fPath);
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
	if (!m_sequences.size()) return;
	Rect srcRect = m_sequences[m_currentSequence].Get();
	m_pRenderComponent->SetSourceRectangle(srcRect.left,srcRect.top , srcRect.width, srcRect.height);
}

void dae::AnimationComponent::AddAnimationSequence(const Rect& sourceRect, int rows, int columns, int sequenceStart, int sequenceLength, float timePerFrame, AnimationSequence::AnimationPlayBack playback)
{
	m_sequences.push_back(AnimationSequence( sourceRect, rows, columns, sequenceStart, sequenceLength,timePerFrame, playback ));
}

void dae::AnimationComponent::AddAnimationSequence(AnimationSequence animSeq)
{
	m_sequences.push_back(animSeq);
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
	int index{};
	if (m_playback == AnimationPlayBack::Reversed || m_playback == AnimationPlayBack::ReverseLooped) {
		index = m_sequenceLength - m_currentIndex;
	}
	else {
		index = m_currentIndex;
	}
	index += m_sequenceStart;

	auto rWidth = m_SourceRectangle.width / m_columns;
	auto rHeight = m_SourceRectangle.height / m_rows;

	int indexX =  index % m_columns;
	int indexY =  index / m_columns;

	auto rLeft = m_SourceRectangle.left + indexX * rWidth;
	auto rTop = m_SourceRectangle.top + indexY * rHeight;
 
	Rect result{ 
		.left = rLeft,
		.top = rTop,
		.width = rWidth,
		.height = rHeight };
	return result;
}

dae::AnimationSequence::AnimationSequence(const Rect& sourceRect, int columns, int rows, int sequenceStart, int sequenceLength, float timePerFrame, AnimationPlayBack playback):
	m_SourceRectangle(sourceRect), m_rows(rows), m_columns(columns), m_sequenceStart(sequenceStart), m_sequenceLength(sequenceLength), m_timePerFrame(timePerFrame), m_playback(playback), m_timer(0.f), m_currentIndex(0)
{
}

dae::AnimationSequence::AnimationSequence(int columns, int rows, int sequenceStart, int sequenceLength, float timePerFrame, AnimationPlayBack playback):
	m_SourceRectangle({ 0,0,0,0 }), m_rows(rows), m_columns(columns), m_sequenceStart(sequenceStart), m_sequenceLength(sequenceLength), m_timePerFrame(timePerFrame), m_playback(playback), m_timer(0.f), m_currentIndex(0)
{
}


void dae::AnimationSequence::Reset()
{
	m_currentIndex = 0;
	m_timer = 0.f;
}
