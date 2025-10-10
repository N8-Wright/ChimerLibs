#pragma once

#ifdef _WIN32
#include <ws2def.h>
#else
#include <sys/types.h>
#endif

namespace Chimer::IO
{
    enum class SocketType
    {
        Stream = SOCK_STREAM,
        Dgram = SOCK_DGRAM,
        Raw = SOCK_RAW,
    };
}
