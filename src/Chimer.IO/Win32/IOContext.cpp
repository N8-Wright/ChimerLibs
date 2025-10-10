#include "Chimer/IO/IOContext.hpp"

#include <winsock2.h>
#include <stdexcept>

namespace Chimer::IO
{
    IOContext::IOContext()
    {
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        {
            throw std::runtime_error("Invalid WSA version");
        }
    }

    IOContext::~IOContext()
    {
        WSACleanup();
    }
}