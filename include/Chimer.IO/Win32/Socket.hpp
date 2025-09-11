#pragma once

#include "Chimer.IO/Win32/OverlappedData.hpp"

#include <winsock2.h>
#include <span>
#include <system_error>

namespace Chimer::IO
{
    class Socket
    {
    private:
        SOCKET m_socketHandle{ INVALID_SOCKET };
        explicit Socket(SOCKET socketHandle);

    public:
        static Socket CreateTcpSocket();
        Socket() = default;
        Socket(int family, int type, int protocol);
        ~Socket();
        Socket(const Socket& other) = delete;
        Socket& operator=(const Socket& other) = delete;
        Socket(Socket&& other) noexcept;
        Socket& operator=(Socket&& other) noexcept;

        void Write(std::span<char> buffer, Events::OnIOCompletion onCompletion) const;
        void Read(std::span<char> buffer, Events::OnIOCompletion onCompletion) const;
        void Bind(const sockaddr_in& addr) const;
        void Listen() const;
        void Accept(const Socket& accept, Events::OnAcceptCompletion onCompletion) const;

        friend class IOCompletion;
    };
}