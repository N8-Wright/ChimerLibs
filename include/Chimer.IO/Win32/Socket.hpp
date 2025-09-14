#pragma once

#include "Chimer.IO/Win32/OverlappedData.hpp"
#include "Chimer.IO/SocketType.hpp"
#include "Chimer.IO/SocketFamily.hpp"
#include "Chimer.IO/SocketProtocol.hpp"

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
        Socket() = default;
        Socket(SocketFamily family, SocketType type, SocketProtocol protocol = SocketProtocol::Unspecified);
        ~Socket();
        Socket(const Socket& other) = delete;
        Socket& operator=(const Socket& other) = delete;
        Socket(Socket&& other) noexcept;
        Socket& operator=(Socket&& other) noexcept;

        void Write(std::span<char> buffer, Events::OnIOCompletion onCompletion) const;
        void Read(std::span<char> buffer, Events::OnIOCompletion onCompletion) const;
        void Bind(const std::optional<std::string>& address, const std::string& port, SocketFamily family, SocketType type) const;
        void Listen() const;
        void Connect(const std::string& address, const std::string& port, SocketType socketType) const;
        void Accept(const Socket& accept, Events::OnAcceptCompletion onCompletion) const;

        friend class IOCompletion;
    };
}