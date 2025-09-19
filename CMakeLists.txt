cmake_minimum_required(VERSION 3.25)
project(ChimerLibs LANGUAGES CXX)

option(CHIMER_TESTING "Enable testing" ON)
option(CHIMER_EXAMPLES "Compile example projects" ${PROJECT_IS_TOP_LEVEL})

add_subdirectory(src)
add_subdirectory(vendor)
