#pragma once

#include "Chimer.Logging/Logger.hpp"

#include <mutex>
#include <thread>
#include <vector>
#include <chrono>

namespace Chimer::Logging
{
    class ThreadedLogger : public Logger
    {
        struct LogMessage
        {
            LogMessage(const LogLevel level,
                const std::string_view message,
                const std::chrono::time_point<std::chrono::system_clock> timestamp)
                : Level(level), Message(message), Timestamp(timestamp)
            {
            }

            LogLevel Level;
            std::string Message;
            std::chrono::time_point<std::chrono::system_clock> Timestamp;
        };

        std::vector<LogMessage> m_toLog;
        std::mutex m_logMutex;
        std::jthread m_logThread;
        std::condition_variable m_notifyLogThread;

    public:
        explicit ThreadedLogger(LogLevel logLevel);
        void Log(LogLevel logLevel, std::string_view message) override;
    protected:
        void ShutdownLogProcessing();
        virtual void LogInternal(LogLevel logLevel,
            std::chrono::time_point<std::chrono::system_clock> timestamp,
            std::string_view message) = 0;

    private:
        void ProcessToLog(const std::stop_token& token);
    };
}
