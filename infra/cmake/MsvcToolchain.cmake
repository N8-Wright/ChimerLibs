include_guard(GLOBAL)
set(CMAKE_C_COMPILER cl)
set(CMAKE_CXX_COMPILER cl)

if(CHIMER_BUILDSYS_SANITIZER STREQUAL "MaxSan")
    # /Zi flag (add debug symbol) is needed when using address sanitizer
    # See C5072: https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-c5072
    #
    # /INCREMENTAL:NO (disable incrmenetal linking) unsupported while using address sanitizer
    # See https://learn.microsoft.com/en-us/cpp/sanitizers/asan-known-issues?view=msvc-170
    set(SANITIZER_FLAGS "/fsanitize=address /Zi")
    add_link_options("/INCREMENTAL:NO")
endif()

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(COMMON_FLAGS "/EHsc /permissive- ${SANITIZER_FLAGS}")

set(CMAKE_CXX_FLAGS_DEBUG_INIT "${COMMON_FLAGS}")
set(CMAKE_C_FLAGS_DEBUG_INIT "${COMMON_FLAGS}")

set(RELEASE_FLAGS "/O2 ${COMMON_FLAGS}")

set(CMAKE_C_FLAGS_RELWITHDEBINFO_INIT "${RELEASE_FLAGS}")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "${RELEASE_FLAGS}")

set(CMAKE_C_FLAGS_RELEASE_INIT "${RELEASE_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "${RELEASE_FLAGS}")

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}")