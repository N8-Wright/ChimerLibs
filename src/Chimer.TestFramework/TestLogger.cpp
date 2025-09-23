#include "Chimer/TestFramework/TestLogger.hpp"

#include "Chimer/Logging/ConsoleLogger.hpp"
#include "Chimer/Logging/FileLogger.hpp"
#include "Chimer/Logging/CompositeLogger.hpp"

#include <chrono>
#include <sstream>

namespace Chimer::TestFramework
{
    Logging::Logger& GetLogger()
    {
        static bool isInitialized = false;
        static Logging::CompositeLogger compositeLogger;
        if (!isInitialized)
        {
            const auto now = std::chrono::system_clock::now();
            const auto time = std::chrono::system_clock::to_time_t(now);
            const auto tm = *std::localtime(&time);

            std::ostringstream fileName;
            fileName << "Test" << '_'
                << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S")
                << ".log";

            static auto fileLogger = std::make_shared<Logging::FileLogger>(Logging::LogLevel::Info, fileName.str());
            static auto consoleLogger = std::make_shared<Logging::ConsoleLogger>(Logging::LogLevel::Info);
            compositeLogger.RegisterLogger(fileLogger);
            compositeLogger.RegisterLogger(consoleLogger);

            consoleLogger->Log(Logging::LogLevel::Info, "Logs can also be found here: " + fileName.str());
            isInitialized = true;
        }

        return compositeLogger;
    }
}