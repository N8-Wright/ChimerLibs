#pragma once

#include <string_view>
#include <vector>
#include <cstdint>
#include <span>

namespace Chimer::Message
{
    struct Message
    {
        using MessageBuffer = std::vector<uint8_t>;
        template<typename T>
        static void Serialize(MessageBuffer& buffer, const T&)
        {
            static_assert(false, "Serialize function not supported");
        }
    };

    template<>
    void Message::Serialize(MessageBuffer& buffer, const int8_t& val);

    template<>
    void Message::Serialize(MessageBuffer& buffer, const uint8_t& val);

    template<>
    void Message::Serialize(MessageBuffer& buffer, const int16_t& val);

    template<>
    void Message::Serialize(MessageBuffer& buffer, const uint16_t& val);

    template<>
    void Message::Serialize(MessageBuffer& buffer, const int32_t& val);

    template<>
    void Message::Serialize(MessageBuffer& buffer, const uint32_t& val);

    template<>
    void Message::Serialize(MessageBuffer& buffer, const std::string_view& str);
}