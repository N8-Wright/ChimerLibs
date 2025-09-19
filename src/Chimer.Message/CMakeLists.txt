add_library(Chimer.Message
  Message.cpp

  ${PROJECT_SOURCE_DIR}/include/Chimer.Message/Message.hpp
)

target_link_libraries(Chimer.Message PUBLIC Microsoft.GSL::GSL)
target_include_directories(Chimer.Message ${WARNING_GUARD} PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
)

add_library(Chimer::Message ALIAS Chimer.Message)
