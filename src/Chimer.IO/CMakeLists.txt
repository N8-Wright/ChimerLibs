add_library(Chimer.IO
  ${PROJECT_SOURCE_DIR}/include/Chimer.IO/Socket.hpp
  ${PROJECT_SOURCE_DIR}/include/Chimer.IO/Events.hpp
)

if (WIN32)
  target_sources(Chimer.IO PRIVATE
    Win32/Socket.cpp

    ${PROJECT_SOURCE_DIR}/include/Chimer.IO/Win32/OverlappedData.hpp
    ${PROJECT_SOURCE_DIR}/include/Chimer.IO/Win32/Socket.hpp
  )
endif()


set_project_warnings(Chimer.IO)
static_link_stl(Chimer.IO)
enable_ipo(Chimer.IO)

target_include_directories(Chimer.IO ${WARNING_GUARD} PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
)

add_library(Chimer::IO ALIAS Chimer.IO)
