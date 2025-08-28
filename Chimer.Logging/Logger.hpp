#pragma once

#include "LogLevel.hpp"

#include <string_view>

namespace Chimer::Logging
{
	class Logger
	{
		LogLevel m_logLevel;

	public:
		virtual ~Logger() = default;
		Logger(LogLevel logLevel);
		LogLevel GetLogLevel() const noexcept;

		virtual void Log(LogLevel logLevel, std::string_view message) const = 0;
	};
}