add_executable(Chimer.Message.Tests
    Main.cpp
    SerializerTests.cpp
)

target_link_libraries(Chimer.Message.Tests Chimer::Message Chimer::TestFramework)

include(CTest)
add_test(NAME Chimer.Message.Tests COMMAND Chimer.Message.Tests)