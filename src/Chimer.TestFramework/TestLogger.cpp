#include "Chimer.TestFramework/TestLogger.hpp"

#include "Chimer.Logging/ConsoleLogger.hpp"

namespace Chimer::TestFramework
{
    Logging::Logger& GetLogger()
    {
        static Logging::ConsoleLogger logger(Logging::LogLevel::Info);
        return logger;
    }
}