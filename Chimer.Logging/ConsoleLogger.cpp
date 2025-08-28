#include "ConsoleLogger.hpp"

#include <iostream>

namespace Chimer::Logging
{
	ConsoleLogger::ConsoleLogger(LogLevel logLevel)
		: Logger(logLevel)
	{
	}

	void ConsoleLogger::Log(LogLevel logLevel, std::string_view message) const
	{
		if (ConfiguredToLog(logLevel))
		{
			std::cout << message << "\n";
		}
	}
}
