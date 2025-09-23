cmake_minimum_required(VERSION 3.28)
project(ChimerLibs LANGUAGES CXX VERSION 0.1)

option(CHIMER_TESTING "Enable testing" ON)
option(CHIMER_EXAMPLES "Compile example projects" ${PROJECT_IS_TOP_LEVEL})

set(GSL_INSTALL ON)
add_subdirectory(src)
add_subdirectory(vendor)

