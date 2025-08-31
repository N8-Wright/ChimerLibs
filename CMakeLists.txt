cmake_minimum_required(VERSION 3.15)
project(ChimerLibs LANGUAGES CXX)

option(CHIMER_TESTING "Enable testing" ON)

if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 23)
endif()

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

include(cmake/CompilerFlags.cmake)
include(cmake/InterproceduralOptimization.cmake)
include(cmake/StaticLinkSTL.cmake)

add_subdirectory(src)
add_subdirectory(vendor)
