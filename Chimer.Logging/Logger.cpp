#include "Logger.hpp"

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
}