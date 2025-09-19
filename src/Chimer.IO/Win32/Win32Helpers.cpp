#pragma once

#include "Win32Helpers.hpp"

namespace Chimer::IO
{
    std::unique_ptr<char, void(*)(char*)> Win32Helpers::GetLastErrorAsString(const DWORD errorCode)
    {
        char* messageBuffer = nullptr;
        if (errorCode == 0)
        {
            return { nullptr, [](char*) static {}};
        }

        //Ask Win32 to give us the string version of that message ID.
        //The parameters we pass in tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
        FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                       nullptr,
                       errorCode,
                       MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT),
                       reinterpret_cast<LPSTR>(&messageBuffer),
                       0,
                       nullptr);

        return { messageBuffer, [](char* ptr) static {
            LocalFree(ptr);
        }};
    }
}