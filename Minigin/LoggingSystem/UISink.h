#pragma once

#include "ILogSink.h"
namespace dae {

	class UISink : public ILogSink 
	{
	public:
		virtual ~UISink() = default;
		virtual void Write(const std::string& message) override;
		virtual void RenderUI() override;
	};
}