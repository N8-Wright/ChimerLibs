#include "Chimer/Message/MessageDeserializer.hpp"

#include <stdexcept>

namespace Chimer::Message
{
    MessageDeserializer::MessageDeserializer(const std::span<uint8_t> buffer) :
        m_buffer(buffer), m_index(0)
    {
    }

    template<>
    int8_t MessageDeserializer::Deserialize<int8_t>()
    {
        if (m_index < m_buffer.size())
        {
            return static_cast<int8_t>(m_buffer[m_index++]);
        }
        else
        {
            throw std::out_of_range("Buffer provided would be accessed out of bounds");
        }
    }
}