add_library(Chimer.Message
  Message.cpp
)

target_sources(Chimer.Message
  PUBLIC
  FILE_SET HEADERS
  BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/../../include"
  FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/Chimer/Message/Message.hpp"
)

find_package(chimer-install-library REQUIRED)
chimer_install_library(Chimer.Message)

target_link_libraries(Chimer.Message PUBLIC Microsoft.GSL::GSL)
target_include_directories(Chimer.Message ${WARNING_GUARD} PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
)

add_library(Chimer::Message ALIAS Chimer.Message)
