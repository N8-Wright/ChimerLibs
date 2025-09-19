#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <span>

namespace Chimer::Message
{
    struct Message
    {
        using MessageBuffer = std::vector<uint8_t>;
        template<typename T>
        static void Serialize(MessageBuffer& buffer, const T& obj)
        {
            static_assert(false, "Serialize function not supported");
        }

        template<typename T>
        static T Deserialize(std::span<char> buffer)
        {
            static_assert(false, "Deserialize function not supported");
            return {};
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
    int8_t Message::Deserialize<int8_t>(std::span<char> buffer);
}