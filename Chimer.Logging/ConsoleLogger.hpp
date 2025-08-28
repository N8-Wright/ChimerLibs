#pragma once

#include "Logger.hpp"

namespace Chimer::Logging
{
	class ConsoleLogger : public Logger
	{
	public:
		ConsoleLogger(LogLevel logLevel);
		void Log(LogLevel logLevel, std::string_view message) const override;
	};
}