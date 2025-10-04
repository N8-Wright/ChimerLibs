add_executable(Chimer.TestFramework.Tests
  NotEqualTests.cpp
  EqualTests.cpp
  FalseTests.cpp
  GreaterThanTests.cpp
  LessThanTests.cpp
  TrueTests.cpp
  Main.cpp
)

target_link_libraries(Chimer.TestFramework.Tests Chimer::TestFramework)

include(CTest)
add_test(NAME Chimer.TestFramework.Tests COMMAND Chimer.TestFramework.Tests)