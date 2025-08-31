add_library(Chimer.TestFramework
  Test.cpp
  TestDriver.cpp
  TestSuite.cpp
  TestCount.cpp
  LogMessages.hpp

  ${PROJECT_SOURCE_DIR}/include/Chimer.TestFramework/Test.hpp
  ${PROJECT_SOURCE_DIR}/include/Chimer.TestFramework/TestDriver.hpp
  ${PROJECT_SOURCE_DIR}/include/Chimer.TestFramework/TestFailureResult.hpp
  ${PROJECT_SOURCE_DIR}/include/Chimer.TestFramework/TestSuite.hpp
  ${PROJECT_SOURCE_DIR}/include/Chimer.TestFramework/TestSuiteResult.hpp
  ${PROJECT_SOURCE_DIR}/include/Chimer.TestFramework/TestCount.hpp
)

set_project_warnings(Chimer.TestFramework)
static_link_stl(Chimer.TestFramework)
enable_ipo(Chimer.TestFramework)
target_link_libraries(Chimer.TestFramework PUBLIC
  Chimer::Logging
  Microsoft.GSL::GSL
)
target_include_directories(Chimer.TestFramework ${WARNING_GUARD} PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
)

add_library(Chimer::TestFramework ALIAS Chimer.TestFramework)
