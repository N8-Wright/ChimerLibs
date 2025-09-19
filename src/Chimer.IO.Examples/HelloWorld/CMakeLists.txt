add_executable(HelloWorldServer HelloServer.cpp)
target_link_libraries(HelloWorldServer Chimer::IO)

add_executable(HelloWorldClient HelloClient.cpp)
target_link_libraries(HelloWorldClient Chimer::IO)