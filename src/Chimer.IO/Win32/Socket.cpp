#include "Chimer/IO/Win32/Socket.hpp"
#include "Chimer/IO/Win32/OverlappedData.hpp"

#include "Win32Helpers.hpp"

#include <system_error>
#include <mswsock.h>
#include <ws2tcpip.h>
namespace Chimer::IO
{
    Socket::Socket(const SOCKET socketHandle) :
        m_socketHandle(socketHandle)
    {
    }

    Socket::Socket(SocketFamily family, SocketType type, SocketProtocol protocol)
    {
        m_socketHandle = WSASocketW(static_cast<int>(family), static_cast<int>(type), static_cast<int>(protocol), nullptr, 0, WSA_FLAG_OVERLAPPED);
        if (m_socketHandle == INVALID_SOCKET)
        {
            const std::error_code ec(WSAGetLastError(), std::system_category());
            throw std::system_error(ec, "Failed to create socket");
        }
    }

    Socket::Socket(Socket&& other) noexcept
        :
        m_socketHandle(std::exchange(other.m_socketHandle, INVALID_SOCKET))
    {
    }

    Socket::~Socket()
    {
        if (m_socketHandle != INVALID_SOCKET)
        {
            // TODO: Maybe don't ignore this error. Can't throw exceptions though...
            closesocket(m_socketHandle);
        }
    }

    Socket& Socket::operator=(Socket&& other) noexcept
    {
        m_socketHandle = std::exchange(other.m_socketHandle, INVALID_SOCKET);
        return *this;
    }

    void Socket::Write(std::span<char> buffer, Events::OnIOCompletion onCompletion) const
    {
        WSABUF wsaBuffer = { static_cast<ULONG>(buffer.size()), buffer.data() };

        // TODO: pool overlapped data structures. Avoid allocating on each read/write.
        OVERLAPPED* data = new OverlappedData(std::move(onCompletion));
        if (constexpr DWORD flags = 0; SOCKET_ERROR == WSASend(m_socketHandle,
                                                               &wsaBuffer,
                                                               1,
                                                               nullptr,
                                                               flags,
                                                               data,
                                                               nullptr))
        {
            if (const auto err = WSAGetLastError(); err != WSA_IO_PENDING)
            {
                const std::error_code ec(err, std::system_category());
                throw std::system_error(ec, "Failed to initiate read on socket");
            }
        }
    }

    void Socket::Read(const std::span<char> buffer, Events::OnIOCompletion onCompletion) const
    {
        WSABUF wsaBuffer = { static_cast<ULONG>(buffer.size()), buffer.data() };

        // TODO: pool overlapped data structures. Avoid allocating on each read/write.
        OVERLAPPED* data = new OverlappedData(std::move(onCompletion));
        DWORD flags = 0;
        if (SOCKET_ERROR == WSARecv(m_socketHandle,
                                    &wsaBuffer,
                                    1,
                                    nullptr,
                                    &flags,
                                    data,
                                    nullptr))
        {
            if (const auto err = WSAGetLastError(); err != WSA_IO_PENDING)
            {
                const std::error_code ec(err, std::system_category());
                throw std::system_error(ec, "Failed to initiate read on socket");
            }
        }
    }

    void Socket::Bind(const std::optional<std::string>& address, const std::string& port, SocketFamily family, SocketType type) const
    {
        addrinfo hints{};
        hints.ai_family = static_cast<int>(family);
        hints.ai_socktype = static_cast<int>(type);
        hints.ai_flags = AI_PASSIVE;

        const char* rawAddress = nullptr;
        if (address)
        {
            rawAddress = address->data();
        }

        addrinfo* servInfo;
        if (const auto status = getaddrinfo(rawAddress, port.data(), &hints, &servInfo); status != 0)
        {
            const auto err = gai_strerror(status);
            const std::error_code ec(status, std::system_category());
            throw std::system_error(ec, err);
        }

        if (SOCKET_ERROR == bind(m_socketHandle, servInfo->ai_addr, static_cast<int>(servInfo->ai_addrlen)))
        {
            freeaddrinfo(servInfo);
            const std::error_code ec(WSAGetLastError(), std::system_category());
            throw std::system_error(ec, "Failed to bind on socket");
        }

        freeaddrinfo(servInfo);
    }

    void Socket::Listen() const
    {
        if (SOCKET_ERROR == listen(m_socketHandle, 200))
        {
            const std::error_code ec(WSAGetLastError(), std::system_category());
            throw std::system_error(ec, "Failed to listen on socket");
        }
    }

    void Socket::Connect(const std::string& address, const std::string& port, SocketType socketType) const
    {
        addrinfo hints{};
        addrinfo* res = nullptr;

        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = static_cast<int>(socketType);

        if (-1 == getaddrinfo(address.c_str(), port.c_str(), &hints, &res))
        {
            const std::error_code ec(errno, std::system_category());
            throw std::system_error(ec, "Failed to resolve getaddrinfo");
        }

        if (SOCKET_ERROR == connect(m_socketHandle, res->ai_addr, static_cast<int>(res->ai_addrlen)))
        {
            const std::error_code ec(WSAGetLastError(), std::system_category());
            throw std::system_error(ec, "Failed to connect on socket");
        }
    }

    void Socket::Accept(const Socket& accept, Events::OnAcceptCompletion onCompletion) const
    {
        GUID guid = WSAID_ACCEPTEX;
        LPFN_ACCEPTEX acceptEx;
        DWORD bytes;

        const int result = WSAIoctl(m_socketHandle,
                                    SIO_GET_EXTENSION_FUNCTION_POINTER,
                                    &guid,
                                    sizeof(guid),
                                    &acceptEx,
                                    sizeof(acceptEx),
                                    &bytes,
                                    nullptr,
                                    nullptr);
        if (result == SOCKET_ERROR)
        {
            throw std::runtime_error("WSAIoctl failed to get AcceptEx");
        }

        DWORD bytesReceived;
        std::vector<char> buffer;
        buffer.resize((sizeof(sockaddr_storage) * 2) + 32);
        const auto overlapped = new OverlappedData(std::move(onCompletion), std::move(buffer));
        auto& [_, movedBuffer] = std::get<AcceptEvent>(overlapped->Event);

        if (FALSE == acceptEx(m_socketHandle,
                              accept.m_socketHandle,
                              movedBuffer.data(),
                              0,
                              sizeof(sockaddr_storage) + 16,
                              sizeof(sockaddr_storage) + 16,
                              &bytesReceived,
                              overlapped))
        {
            if (const auto err = WSAGetLastError(); err != ERROR_IO_PENDING)
            {
                const std::error_code ec(err, std::system_category());
                throw std::system_error(ec, "Failed to initiate accept on socket");
            }
        }
    }
}