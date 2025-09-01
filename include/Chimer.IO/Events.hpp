#pragma once

#include <functional>
namespace Chimer::IO
{
    struct Events
    {
        using OnIOCompletion = std::function<void(size_t bytesTransferred)>;
    };
}