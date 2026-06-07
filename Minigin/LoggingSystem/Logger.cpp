#include "Logger.h"

void dae::Logger::RenderUI()
{
	for (auto& sink : m_pSinks) {
		sink->RenderUI();
	}
}

void dae::Logger::Write(const std::string message)
{
	for (auto& sink : m_pSinks) {
		sink->Write(message);
	}
}

void dae::Logger::AddSink(std::unique_ptr<ILogSink> sink)
{
	m_pSinks.push_back(std::move(sink));
}
