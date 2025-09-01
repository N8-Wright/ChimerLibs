#pragma once

#include "Chimer.Logging/ThreadedLogger.hpp"

#include <fstream>
#include <filesystem>

namespace Chimer::Logging
{
    class FileLogger final : public ThreadedLogger
    {
        std::fstream m_file;
    public:
        FileLogger(LogLevel logLevel, const std::filesystem::path& filePath);
        ~FileLogger() override;
        explicit FileLogger(const ThreadedLogger&) = delete;
        FileLogger& operator=(const FileLogger&) = delete;
        FileLogger(FileLogger&&) = delete;
        FileLogger& operator=(FileLogger&&) = delete;

    protected:
        void LogInternal(LogLevel logLevel,
            std::chrono::time_point<std::chrono::system_clock> timestamp,
            std::string_view message) override;
    };
}