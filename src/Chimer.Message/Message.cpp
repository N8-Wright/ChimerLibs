#include "Chimer.Message/Message.hpp"

#ifdef _WIN32
#include <winsock2.h>
#else
#include <arpa/inet.h>
#endif

#include <array>

namespace Chimer::Message
{
    template<>
    void Message::Serialize<signed char>(MessageBuffer& buffer, const int8_t& val)
    {
        buffer.push_back(val);
    }

    template<>
    void Message::Serialize(MessageBuffer& buffer, const uint8_t& val)
    {
        buffer.push_back(val);
    }

    template<>
    void Message::Serialize(MessageBuffer& buffer, const int16_t& val)
    {
        const auto networkOrderVal = htons(val);
        static_assert(sizeof(networkOrderVal) == sizeof(val), "Network order doesn't match");
        std::array<char, sizeof(val)> valBuffer;
        memcpy(valBuffer.data(), &networkOrderVal, sizeof(networkOrderVal));

        buffer.insert(buffer.end(), valBuffer.begin(), valBuffer.end());
    }

    template<>
    void Message::Serialize(MessageBuffer& buffer, const uint16_t& val)
    {
        Serialize(buffer, static_cast<int16_t>(val));
    }

    template<>
    void Message::Serialize(MessageBuffer& buffer, const int32_t& val)
    {
        const auto networkOrderVal = htonl(val);
        static_assert(sizeof(networkOrderVal) == sizeof(val), "Network order doesn't match");
        std::array<char, sizeof(val)> valBuffer;
        memcpy(valBuffer.data(), &networkOrderVal, sizeof(networkOrderVal));

        buffer.insert(buffer.end(), valBuffer.begin(), valBuffer.end());
    }

    template<>
    void Message::Serialize(MessageBuffer& buffer, const uint32_t& val)
    {
        Serialize(buffer, static_cast<int32_t>(val));
    }
}