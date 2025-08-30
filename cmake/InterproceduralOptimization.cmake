function(enable_ipo target_name)
  include(CheckIPOSupported)
  check_ipo_supported(RESULT result OUTPUT output)
  if (result)
    if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
      set_target_properties(${target_name} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION ON
      )

      if (MSVC)
        target_compile_options(${target_name} PUBLIC /Gy)
      endif()
    endif()
  else()
    message(SEND_ERROR "IPO is not supported: ${output}")
  endif()
endfunction()
