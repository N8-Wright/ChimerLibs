#include "Chimer/Logging/Logger.hpp"

namespace Chimer::Logging
{
    Logger::Logger(const LogLevel logLevel) :
        m_logLevel(logLevel)
    {
    }

    LogLevel Logger::GetLogLevel() const noexcept
    {
        return m_logLevel;
    }

    bool Logger::ConfiguredToLog(const LogLevel logLevel) const noexcept
    {
        return m_logLevel >= logLevel;
    }
}
