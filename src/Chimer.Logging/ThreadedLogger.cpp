#include "Chimer.Logging/ThreadedLogger.hpp"

#include <iostream>
namespace Chimer::Logging
{
    ThreadedLogger::ThreadedLogger(const LogLevel logLevel) :
        Logger(logLevel)
    {
        m_logThread = std::jthread([this](const std::stop_token& token) {
            ProcessToLog(token);
        });
    }

    void ThreadedLogger::Log(LogLevel logLevel, std::string_view message)
    {
        std::unique_lock lock(m_logMutex);
        m_toLog.emplace_back(logLevel, message, std::chrono::system_clock::now());
        m_notifyLogThread.notify_one();
    }

    void ThreadedLogger::ShutdownLogProcessing()
    {
        m_logThread.request_stop();
        m_notifyLogThread.notify_all();
        m_logThread.join();
    }

    void ThreadedLogger::ProcessToLog(const std::stop_token& token)
    {
        while (true)
        {
            try
            {
                std::vector<LogMessage> batch;
                {
                    std::unique_lock lock(m_logMutex);
                    m_notifyLogThread.wait(lock, [this, &token] {
                        return token.stop_requested() || !m_toLog.empty();
                    });

                    if (token.stop_requested() && m_toLog.empty())
                    {
                        break;
                    }

                    std::swap(batch, m_toLog);
                }

                for (const auto& entry : batch)
                {
                    LogInternal(entry.Level, entry.Timestamp, entry.Message);
                }
            }
            catch (const std::exception& e)
            {
                std::cerr << e.what();
            }
            catch (...)
            {
                std::cerr << "Unknown exception";
            }
        }
    }
}