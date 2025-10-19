#include "Chimer/TestFramework/Test.hpp"
#include "Chimer/Message/Message.hpp"
#include "Chimer/Message/MessageDeserializer.hpp"

#include <array>
#include <span>

using namespace Chimer::Message;

TEST_SUITE_DEFINE(SerializerTests);
TEST(SerializerTests, int8_t)
{
    // Arrange
    Message::MessageBuffer buffer;
    Message::Serialize(buffer, static_cast<int8_t>(233));

    MessageDeserializer deserializer{ std::span<uint8_t>(buffer) };

    // Act
    const auto result = deserializer.Deserialize<int8_t>();

    // Assert
    AssertEqual(static_cast<int8_t>(233), result);
}

TEST(SerializerTests, int8_t_TooFar)
{
    // Arrange
    std::array<uint8_t, 3> buffer{};
    MessageDeserializer deserializer{ std::span(buffer).subspan(0, 2) };

    deserializer.Deserialize<int8_t>();
    deserializer.Deserialize<int8_t>();

    // Act
    const auto exception = AssertThrows([&deserializer]() {
        deserializer.Deserialize<int8_t>();
    });

    // Assert
    AssertExceptionIs<std::out_of_range>(exception, [](const auto&) {
    });
}

TEST(SerializerTests, int16_t)
{
    // Arrange
    Message::MessageBuffer buffer;
    Message::Serialize(buffer, static_cast<int16_t>(-233));

    MessageDeserializer deserializer{ std::span<uint8_t>(buffer) };

    // Act
    const auto result = deserializer.Deserialize<int16_t>();

    // Assert
    AssertEqual(static_cast<int16_t>(-233), result);
}

TEST(SerializerTests, int16_t_TooFar)
{
    // Arrange
    std::array<uint8_t, 4> buffer{};
    MessageDeserializer deserializer{ std::span(buffer).subspan(0, 3) };

    deserializer.Deserialize<int16_t>();

    // Act
    const auto exception = AssertThrows([&deserializer]() {
        deserializer.Deserialize<int16_t>();
    });

    // Assert
    AssertExceptionIs<std::out_of_range>(exception, [](const auto&) {
    });
}

TEST(SerializerTests, uint16_t)
{
    // Arrange
    Message::MessageBuffer buffer;
    Message::Serialize(buffer, static_cast<uint16_t>(2333));

    MessageDeserializer deserializer{ std::span<uint8_t>(buffer) };

    // Act
    const auto result = deserializer.Deserialize<uint16_t>();

    // Assert
    AssertEqual(static_cast<uint16_t>(2333), result);
}

TEST(SerializerTests, uint16_t_TooFar)
{
    // Arrange
    std::array<uint8_t, 4> buffer{};
    MessageDeserializer deserializer{ std::span(buffer).subspan(0, 3) };

    deserializer.Deserialize<uint16_t>();

    // Act
    const auto exception = AssertThrows([&deserializer]() {
        deserializer.Deserialize<uint16_t>();
    });

    // Assert
    AssertExceptionIs<std::out_of_range>(exception, [](const auto&) {
    });
}