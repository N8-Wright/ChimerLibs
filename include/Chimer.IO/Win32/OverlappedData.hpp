#pragma once

#include "Chimer.IO/Events.hpp"

#include <winsock2.h>

namespace Chimer::IO
{
    struct OverlappedData : public OVERLAPPED
    {
        explicit OverlappedData(Events::OnIOCompletion&& onCompletion)
            : OnCompletion(std::move(onCompletion))
        {
        }

        Events::OnIOCompletion OnCompletion;
    };
}