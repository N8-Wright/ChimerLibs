#pragma once

#include "Chimer.IO/Win32/OverlappedData.hpp"

#include <span>
#include <system_error>
#include <string_view>
#include <optional>
#include <cstdint>

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
        void Bind(const std::optional<std::string_view>& address, std::string_view port, int family, int type) const;
        void Listen() const;
        void Accept(const Socket& accept, Events::OnAcceptCompletion onCompletion) const;

        friend class IOCompletion;
    };
}