#include "FileSink.h"

dae::FileSink::FileSink(const std::string& filePath):
	outputFile(filePath)
{
}

void dae::FileSink::Write(const std::string& message)
{
	outputFile <<"[Minigin] : " << message << std::endl;
}
