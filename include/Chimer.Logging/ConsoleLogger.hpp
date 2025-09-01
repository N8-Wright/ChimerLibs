#pragma once

#include "Chimer.Logging/ThreadedLogger.hpp"

namespace Chimer::Logging
{
    class ConsoleLogger final : public ThreadedLogger
    {
    public:
        explicit ConsoleLogger(LogLevel logLevel);
        ~ConsoleLogger() override;
        explicit ConsoleLogger(const ThreadedLogger&) = delete;
        ConsoleLogger& operator=(const ConsoleLogger&) = delete;
        ConsoleLogger(ConsoleLogger&&) = delete;
        ConsoleLogger& operator=(ConsoleLogger&&) = delete;

    protected:
        void LogInternal(LogLevel logLevel,
                         std::chrono::time_point<std::chrono::system_clock> timestamp,
                         std::string_view message) override;
    };
}