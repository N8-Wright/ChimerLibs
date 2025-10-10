#pragma once

#include "Chimer/IO/Events.hpp"

#include <winsock2.h>
#include <vector>
#include <variant>

namespace Chimer::IO
{
    struct ReadWriteEvent
    {
        Events::OnIOCompletion OnIOCompletion;
    };

    struct AcceptEvent
    {
        Events::OnAcceptCompletion OnAcceptCompletion;
        std::vector<char> Data;
    };

    struct OverlappedData : public OVERLAPPED
    {
        explicit OverlappedData(Events::OnIOCompletion&& onCompletion)
            : OVERLAPPED{}, Event(ReadWriteEvent {std::move(onCompletion)})
        {
        }

        OverlappedData(Events::OnAcceptCompletion&& onCompletion, std::vector<char>&& data)
            : OVERLAPPED{}, Event(AcceptEvent {std::move(onCompletion), std::move(data)})
        {
        }

        std::variant<ReadWriteEvent, AcceptEvent> Event;
    };
}