#include "Chimer.Logging/FileLogger.hpp"

namespace Chimer::Logging
{

    FileLogger::FileLogger(LogLevel logLevel, const std::filesystem::path& filePath)
        : ThreadedLogger(logLevel), m_file(filePath, std::fstream::out | std::fstream::app)
    {
    }

    FileLogger::~FileLogger()
    {
        ShutdownLogProcessing();
    }

    void FileLogger::LogInternal(const LogLevel logLevel,
        const std::chrono::time_point<std::chrono::system_clock> timestamp,
        const std::string_view message)
    {
        const std::time_t time = std::chrono::system_clock::to_time_t(timestamp);
        m_file << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S") << " [" << logLevel << "] - " << message << "\n";
    }
}