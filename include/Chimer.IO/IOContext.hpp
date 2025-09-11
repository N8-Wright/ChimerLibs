#pragma once

namespace Chimer::IO
{
    class IOContext
    {
    public:
        IOContext();
        ~IOContext();

        IOContext(const IOContext&) = delete;
        IOContext& operator=(const IOContext&) = delete;
        IOContext(IOContext&&) = delete;
        IOContext& operator=(IOContext&&) = delete;
    };
}