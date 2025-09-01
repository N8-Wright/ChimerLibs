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
        m_toLog.emplace(logLevel, message);
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
                std::unique_lock lock(m_logMutex);
                m_notifyLogThread.wait(lock, [this, &token] {
                    return token.stop_requested() || !m_toLog.empty();
                });

                if (token.stop_requested() && m_toLog.empty())
                {
                    break;
                }

                auto front = std::move(m_toLog.front());
                m_toLog.pop();
                lock.unlock();

                LogInternal(front.Level, front.Message);
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

        // Drain logs
        std::unique_lock lock(m_logMutex);
        while (!m_toLog.empty())
        {
            auto front = std::move(m_toLog.front());
            m_toLog.pop();

            try
            {
                LogInternal(front.Level, front.Message);
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