#include "Chimer/IO/Win32/IOCompletion.hpp"
#include "Chimer/IO/Win32/OverlappedData.hpp"
#include "Chimer/IO/Win32/Socket.hpp"

#include "Win32Helpers.hpp"
#include "LogMessages.hpp"

#include <system_error>
#include <iostream>

namespace Chimer::IO
{
    void IOCompletion::IOWorker(const std::stop_token& token)
    {
        while (!token.stop_requested())
        {
            DWORD numberOfBytesTransferred;
            ULONG_PTR completionKey;
            OverlappedData* data = nullptr;

            const BOOL result = GetQueuedCompletionStatus(m_ioCompletionPort,
                                                          &numberOfBytesTransferred,
                                                          &completionKey,
                                                          reinterpret_cast<LPOVERLAPPED*>(&data),
                                                          1000);
            if (!result)
            {
                const DWORD error = GetLastError();
                if (error != WAIT_TIMEOUT)
                {
                    LogMessages::Win32Error(m_logger, std::string_view("IOCompletion error"), error);
                }

                delete data;
                if (error == ERROR_ABANDONED_WAIT_0)
                {
                    break;
                }

                continue;
            }

            if (const auto clientSocket = completionKey; clientSocket == NULL)
            {
                break; // Exit thread if socket is null
            }

            try
            {
                if (std::holds_alternative<ReadWriteEvent>(data->Event))
                {
                    const auto& [OnIOCompletion] = std::get<ReadWriteEvent>(data->Event);
                    OnIOCompletion(numberOfBytesTransferred);
                }
                else if (std::holds_alternative<AcceptEvent>(data->Event))
                {
                    const auto& [OnAcceptCompletion, _] = std::get<AcceptEvent>(data->Event);
                    OnAcceptCompletion();
                }
            }
            catch (const std::exception& e)
            {
                LogMessages::IOCompletionWorkerException(m_logger, e);
            }
            catch (...)
            {
                LogMessages::IOCompletionWorkerUnknownError(m_logger);
            }

            delete data;
        }
    }

    IOCompletion::IOCompletion(std::shared_ptr<Logging::Logger> logger) :
        m_logger(std::move(logger))
    {
        // Create the completion port with nothing associated with it yet.
        m_ioCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE,
                                                    nullptr,
                                                    0,
                                                    0);
        if (m_ioCompletionPort == nullptr)
        {
            const auto err = GetLastError();
            const std::error_code ec(static_cast<int>(err), std::system_category());
            throw std::system_error(ec, "Failed to create io completion port");
        }
    }

    void IOCompletion::Run(const std::stop_token& token)
    {
        const auto numThreads = std::thread::hardware_concurrency();
        for (unsigned int i = 0; i < numThreads; i++)
        {
            m_workers.emplace_back([this](const auto& passedToken) {
                IOCompletion::IOWorker(passedToken);
            }, token);
        }

        for (auto& worker : m_workers)
        {
            worker.join();
        }
    }

    void IOCompletion::Add(const Socket& socket) const
    {
        if (socket.m_socketHandle == INVALID_SOCKET)
        {
            return;
        }

        if (nullptr == CreateIoCompletionPort(reinterpret_cast<HANDLE>(socket.m_socketHandle),
                                              m_ioCompletionPort,
                                              reinterpret_cast<ULONG_PTR>(this),
                                              0))
        {
            const std::error_code ec(static_cast<int>(GetLastError()), std::system_category());
            throw std::system_error(ec, "Failed to add socket to completion port");
        }
    }
}