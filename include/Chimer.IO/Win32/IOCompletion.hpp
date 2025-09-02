#pragma once

#include "Chimer.Logging/Logger.hpp"

#include <winsock2.h>

#include <vector>
#include <thread>

namespace Chimer::IO
{
    class Socket;
    class IOCompletion
    {
        HANDLE m_ioCompletionPort { INVALID_HANDLE_VALUE };
        std::vector<std::jthread> m_workers;
        std::shared_ptr<Logging::Logger> m_logger;

        void IOWorker(const std::stop_token& token);
    public:
        explicit IOCompletion(std::shared_ptr<Logging::Logger> logger);
        void Run(const std::stop_token& token);
        void Add(const Socket& socket);
    };
}