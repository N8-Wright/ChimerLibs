add_library(Chimer.Logging
  ConsoleLogger.cpp
  ThreadedLogger.cpp
  Logger.cpp
  FileLogger.cpp
  CompositeLogger.cpp
)

target_sources(Chimer.Logging
  PUBLIC
  FILE_SET HEADERS
  BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/../../include"
  FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/Chimer/Logging/ConsoleLogger.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/Chimer/Logging/Logger.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/Chimer/Logging/LoggerDelegate.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/Chimer/Logging/LogLevel.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/Chimer/Logging/ThreadedLogger.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/Chimer/Logging/FileLogger.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/Chimer/Logging/CompositeLogger.hpp"
)

find_package(chimer-install-library REQUIRED)
chimer_install_library(Chimer.Logging)

target_link_libraries(Chimer.Logging INTERFACE Microsoft.GSL::GSL)
target_include_directories(Chimer.Logging ${WARNING_GUARD} PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
)

add_library(Chimer::Logging ALIAS Chimer.Logging)
