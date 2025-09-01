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
        explicit Logger(LogLevel logLevel);
        [[nodiscard]] LogLevel GetLogLevel() const noexcept;
        [[nodiscard]] bool ConfiguredToLog(LogLevel logLevel) const noexcept;

        virtual void Log(LogLevel logLevel, std::string_view message) = 0;
    };
}