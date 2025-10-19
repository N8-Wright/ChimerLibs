#include "Chimer/Message/MessageDeserializer.hpp"

#include <stdexcept>

#ifdef _WIN32
#include <winsock2.h>
#else
#include <arpa/inet.h>
#endif

namespace Chimer::Message
{
    MessageDeserializer::MessageDeserializer(const std::span<uint8_t> buffer) :
        m_buffer(buffer), m_bufferIndex(0)
    {
    }

    template<>
    int8_t MessageDeserializer::Deserialize<int8_t>()
    {
        if (m_bufferIndex < m_buffer.size())
        {
            return static_cast<int8_t>(m_buffer[m_bufferIndex++]);
        }

        throw std::out_of_range("Buffer provided would be accessed out of bounds");
    }

    template<>
    int16_t MessageDeserializer::Deserialize<int16_t>()
    {
        return static_cast<int16_t>(Deserialize<uint16_t>());
    }

    template<>
    uint16_t MessageDeserializer::Deserialize<uint16_t>()
    {
        uint16_t value;
        if (m_bufferIndex + sizeof(value) <= m_buffer.size())
        {
            memcpy(&value, m_buffer.data() + m_bufferIndex, sizeof(value));
            m_bufferIndex += sizeof(value);
            const auto converted = ntohs(value);
            static_assert(sizeof(converted) == sizeof(value), "Network order doesn't match");
            return converted;
        }

        throw std::out_of_range("Buffer provided would be accessed out of bounds");
    }
}