#pragma once

#include "ILogSink.h"
#include <fstream>

namespace dae{
	
	class FileSink : public ILogSink{
	private:
		std::ofstream outputFile;
	public:
		virtual ~FileSink() = default;
		explicit FileSink(const std::string& filePath);

		virtual void Write(const std::string& message) override;
	};
}