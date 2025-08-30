add_library(Chimer.Logging
  ConsoleLogger.cpp
  Logger.cpp

  ${PROJECT_SOURCE_DIR}/include/Chimer.Logging/ConsoleLogger.hpp
  ${PROJECT_SOURCE_DIR}/include/Chimer.Logging/Logger.hpp
  ${PROJECT_SOURCE_DIR}/include/Chimer.Logging/LoggerDelegate.hpp
  ${PROJECT_SOURCE_DIR}/include/Chimer.Logging/LogLevel.hpp
)

set_project_warnings(Chimer.Logging)
static_link_stl(Chimer.Logging)
enable_ipo(Chimer.Logging)

target_include_directories(Chimer.Logging ${WARNING_GUARD} PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
)

add_library(Chimer::Logging ALIAS Chimer.Logging)
