#include "Chimer.Logging/Logger.hpp"

namespace Chimer::Logging
{
	Logger::Logger(LogLevel logLevel)
		: m_logLevel(logLevel)
	{
	}

	LogLevel Logger::GetLogLevel() const noexcept
	{
		return m_logLevel;
	}

	bool Logger::ConfiguredToLog(LogLevel logLevel) const noexcept
	{
		return m_logLevel >= logLevel;
	}
}
