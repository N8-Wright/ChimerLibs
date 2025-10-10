add_library(Chimer.IO)

if (WIN32)
  target_sources(Chimer.IO PRIVATE
    Win32/Socket.cpp
    Win32/IOCompletion.cpp
    Win32/Win32Helpers.cpp
    Win32/Win32Helpers.hpp
    Win32/IOContext.cpp
  )

  target_link_libraries(Chimer.IO PUBLIC Ws2_32)
endif()

target_sources(Chimer.IO
  PUBLIC
  FILE_SET HEADERS
  BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/../../include"
  FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/Chimer/IO/Socket.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/Chimer/IO/Events.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/Chimer/IO/IOCompletion.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/Chimer/IO/IOContext.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/Chimer/IO/Win32/OverlappedData.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/Chimer/IO/Win32/Socket.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/Chimer/IO/Win32/IOCompletion.hpp"
)

find_package(chimer-install-library REQUIRED)
chimer_install_library(Chimer.IO)

target_link_libraries(Chimer.IO PUBLIC Chimer.Logging)
target_include_directories(Chimer.IO ${WARNING_GUARD} PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
)

add_library(Chimer::IO ALIAS Chimer.IO)
