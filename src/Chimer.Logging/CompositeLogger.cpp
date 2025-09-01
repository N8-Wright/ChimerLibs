#include "Chimer.Logging/CompositeLogger.hpp"

namespace Chimer::Logging
{
    CompositeLogger::CompositeLogger()
        : Logger(LogLevel::Critial)
    {
    }

    void CompositeLogger::RegisterLogger(std::shared_ptr<Logger> logger)
    {
        m_logLevel = std::max(logger->GetLogLevel(), m_logLevel);
        m_loggers.push_back(std::move(logger));
    }

    void CompositeLogger::Log(const LogLevel logLevel, std::string&& message)
    {
        const auto owningMessage= std::move(message);
        for (const auto& logger : m_loggers)
        {
            if (logger->ConfiguredToLog(logLevel))
            {
                auto copy = owningMessage;
                logger->Log(logLevel, std::move(copy));
            }
        }
    }
}