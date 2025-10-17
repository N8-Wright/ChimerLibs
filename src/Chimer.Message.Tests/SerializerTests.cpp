#include "Chimer/TestFramework/Test.hpp"
#include "Chimer/Message/Message.hpp"
#include "Chimer/Message/MessageDeserializer.hpp"

#include <array>

using namespace Chimer::Message;

TEST_SUITE_DEFINE(SerializerTests);
TEST(SerializerTests, int8_t)
{
    // Arrange
    Message::MessageBuffer buffer;
    Message::Serialize(buffer, static_cast<int8_t>(233));

    MessageDeserializer deserializer { std::span<uint8_t>(buffer) };

    // Act
    const auto result = deserializer.Deserialize<int8_t>();

    // Assert
    ASSERT_EQ(static_cast<int8_t>(233), result);
}

TEST(SerializerTests, TooFar)
{
    // Arrange
    std::array<uint8_t, 2> buffer;
    MessageDeserializer deserializer { std::span(buffer) };

    deserializer.Deserialize<int8_t>();
    deserializer.Deserialize<int8_t>();

    // Act
    this->AssertThrows([&deserializer]() {
        deserializer.Deserialize<int8_t>();
    });
}