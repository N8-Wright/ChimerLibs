#pragma once

#include <span>

namespace Chimer::Message
{
    class MessageDeserializer
    {
        std::span<uint8_t> m_buffer;
        std::size_t m_index;

    public:
        MessageDeserializer(std::span<uint8_t> buffer);
        template<typename T>
        T Deserialize()
        {
            static_assert(false, "Invalid usage of deserialize");
            return {};
        }
    };

    template<>
    int8_t MessageDeserializer::Deserialize<int8_t>();
}