add_executable(Chimer.TestFramework.Tests
  NotEqualTests.cpp
  EqualTests.cpp
  FalseTests.cpp
  GreaterThanTests.cpp
  LessThanTests.cpp
  TrueTests.cpp
  Main.cpp
)

set_project_warnings(Chimer.TestFramework.Tests)
static_link_stl(Chimer.TestFramework.Tests)
enable_ipo(Chimer.TestFramework.Tests)
target_link_libraries(Chimer.TestFramework.Tests Chimer::TestFramework)
