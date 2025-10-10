#pragma once

#ifdef _WIN32
#include <ws2def.h>
#else
#include <sys/types.h>
#endif

namespace Chimer::IO
{
    enum class SocketFamily
    {
        Unspecified = AF_UNSPEC,
        Unix = AF_UNIX,
        Inet = AF_INET,
        Inet6 = AF_INET6,
    };
}
