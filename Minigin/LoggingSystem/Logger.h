#pragma once

#include "Logger.h"
#include "ILogSink.h"

#include <memory>
#include <vector>

namespace dae {
	class Logger 
	{
		std::vector<std::unique_ptr<ILogSink>> m_pSinks;
	
	public:
		void RenderUI();
		void Write(const std::string);
		void AddSink(std::unique_ptr<ILogSink>);
	};
}