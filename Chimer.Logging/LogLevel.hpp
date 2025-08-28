#pragma once

#include <ostream>

namespace Chimer::Logging
{
	enum class LogLevel
	{
		Critial = 0,
		Error = 1,
		Warning = 2,
		Info = 3,
		Detail = 4,
	};

	inline std::ostream& operator<<(std::ostream& os, LogLevel level)
	{
		switch (level)
		{
			case LogLevel::Critial: os << "Critical"; break;
			case LogLevel::Error:   os << "Error";    break;
			case LogLevel::Warning: os << "Warning";  break;
			case LogLevel::Info:    os << "Info";     break;
			case LogLevel::Detail:  os << "Detail";   break;
			default:                os << "Unknown";  break;
		}

		return os;
	}
}