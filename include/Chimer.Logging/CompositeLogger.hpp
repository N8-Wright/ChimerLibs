#pragma once

#include "Logger.hpp"

#include <vector>
#include <memory>

namespace Chimer::Logging
{
    class CompositeLogger final : public Logger
    {
        std::vector<std::shared_ptr<Logger>> m_loggers;
    public:
        CompositeLogger();
        void RegisterLogger(std::shared_ptr<Logger> logger);
        void Log(LogLevel logLevel, std::string&& message) override;
    };
}