#pragma once

#include <windows.h>
#include <memory>

namespace Chimer::IO
{
    struct Win32Helpers
    {
        static std::unique_ptr<char, void(*)(char*)>  GetLastErrorAsString(DWORD errorCode);
    };
}