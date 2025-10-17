add_library(Chimer.TestFramework
  Test.cpp
  TestDriver.cpp
  TestSuite.cpp
  TestCount.cpp
  LogMessages.hpp
  TestLogger.cpp
  TestException.cpp
)

target_sources(Chimer.TestFramework
  PUBLIC
  FILE_SET HEADERS
  BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/../../include"
  FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/Chimer/TestFramework/Test.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/Chimer/TestFramework/TestDriver.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/Chimer/TestFramework/TestFailureResult.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/Chimer/TestFramework/TestSuite.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/Chimer/TestFramework/TestSuiteResult.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/Chimer/TestFramework/TestCount.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/Chimer/TestFramework/TestLogger.hpp"
)

find_package(chimer-install-library REQUIRED)
chimer_install_library(Chimer.TestFramework)

target_link_libraries(Chimer.TestFramework PUBLIC
  Chimer::Logging
)

target_link_libraries(Chimer.TestFramework INTERFACE
  Microsoft.GSL::GSL
)

target_include_directories(Chimer.TestFramework ${WARNING_GUARD} PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
)

add_library(Chimer::TestFramework ALIAS Chimer.TestFramework)
