#pragma once

#include "Chimer/Logging/LoggerDelegate.hpp"

#include "Win32Helpers.hpp"

#include <sstream>
namespace Chimer::IO
{
    struct LogMessages
    {
        static inline auto Win32Error = Logging::MakeLoggerDelegate(
            Logging::LogLevel::Error,
            [](const std::string_view message, const DWORD errorCode) static {
                const auto errorStr = Win32Helpers::GetLastErrorAsString(errorCode);
                std::stringstream ss;
                ss << "Error: " << errorCode << "(" << errorStr.get() << ") " << message;
                return ss.str();
            });

        static inline auto IOCompletionWorkerException = Logging::MakeLoggerDelegate(
            Logging::LogLevel::Error,
            [](const std::exception& e) static {
                std::stringstream ss;
                ss << "Exception occurred in IOCompletion worker: " << e.what();
                return ss.str();
            });

        static inline auto IOCompletionWorkerUnknownError = Logging::MakeLoggerDelegate(
            Logging::LogLevel::Error,
            []() static {
                return "Unknown exception occurred in IOCompletion worker";
            });
    };
}