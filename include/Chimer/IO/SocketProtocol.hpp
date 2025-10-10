#pragma once

#ifdef _WIN32
#include <ws2def.h>
#else
#include <sys/types.h>
#endif

namespace Chimer::IO
{
    enum class SocketProtocol
    {
        Unspecified = 0,
        Tcp = IPPROTO_TCP,
        Udp = IPPROTO_UDP,
    };
}