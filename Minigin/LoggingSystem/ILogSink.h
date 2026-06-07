#pragma once 
#include <sstream>

namespace dae 
{
	class ILogSink {
	public:
		ILogSink() = default;
		virtual ~ILogSink() = default;
		virtual void Write(const std::string& message) = 0;
		virtual void RenderUI() = 0;
	};
}
