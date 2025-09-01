#include "Chimer.Logging/ConsoleLogger.hpp"

#include <iostream>
#include <chrono>

namespace Chimer::Logging
{
    ConsoleLogger::ConsoleLogger(const LogLevel logLevel) :
        ThreadedLogger(logLevel)
    {
    }

    ConsoleLogger::~ConsoleLogger()
    {
        ShutdownLogProcessing();
    }

    void ConsoleLogger::LogInternal(const LogLevel logLevel, const std::string_view message)
    {
        const auto now = std::chrono::system_clock::now();
        const std::time_t time = std::chrono::system_clock::to_time_t(now);
        std::cout << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S") << " [" << logLevel << "] - " << message << "\n";
    }
}
