add_library(Chimer.IO
  ${PROJECT_SOURCE_DIR}/include/Chimer.IO/Socket.hpp
  ${PROJECT_SOURCE_DIR}/include/Chimer.IO/Events.hpp
  ${PROJECT_SOURCE_DIR}/include/Chimer.IO/IOCompletion.hpp
  ${PROJECT_SOURCE_DIR}/include/Chimer.IO/IOContext.hpp
)

if (WIN32)
  target_sources(Chimer.IO PRIVATE
    Win32/Socket.cpp
    Win32/IOCompletion.cpp
    Win32/Win32Helpers.cpp
    Win32/Win32Helpers.hpp
    Win32/IOContext.cpp

    ${PROJECT_SOURCE_DIR}/include/Chimer.IO/Win32/OverlappedData.hpp
    ${PROJECT_SOURCE_DIR}/include/Chimer.IO/Win32/Socket.hpp
    ${PROJECT_SOURCE_DIR}/include/Chimer.IO/Win32/IOCompletion.hpp
  )

  target_link_libraries(Chimer.IO PUBLIC Ws2_32)
endif()


set_project_warnings(Chimer.IO)
static_link_stl(Chimer.IO)
enable_ipo(Chimer.IO)

target_link_libraries(Chimer.IO PUBLIC Chimer.Logging)
target_include_directories(Chimer.IO ${WARNING_GUARD} PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
)

add_library(Chimer::IO ALIAS Chimer.IO)
