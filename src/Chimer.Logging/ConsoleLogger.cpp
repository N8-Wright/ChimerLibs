#include "Chimer.Logging/ConsoleLogger.hpp"

#include <iostream>
#include <chrono>

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
			const auto now = std::chrono::system_clock::now();
			std::time_t time = std::chrono::system_clock::to_time_t(now);
			std::cout << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S") << " [" << logLevel << "] - " << message << "\n";
		}
	}
}
