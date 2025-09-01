#pragma once

#include "Chimer.Logging/Logger.hpp"

#include <mutex>
#include <thread>
#include <queue>

namespace Chimer::Logging
{
    class ThreadedLogger : public Logger
    {
        struct LogMessage
        {
            LogMessage(const LogLevel level, const std::string_view message)
                : Level(level), Message(message)
            {
            }

            LogLevel Level;
            std::string Message;
        };

        std::queue<LogMessage> m_toLog;
        std::mutex m_logMutex;
        std::jthread m_logThread;
        std::condition_variable m_notifyLogThread;

    public:
        explicit ThreadedLogger(LogLevel logLevel);
        void Log(LogLevel logLevel, std::string_view message) override;
    protected:
        void ShutdownLogProcessing();
        virtual void LogInternal(LogLevel logLevel, std::string_view message) = 0;

    private:
        void ProcessToLog(const std::stop_token& token);
    };
}
