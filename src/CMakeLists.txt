add_subdirectory(Chimer.Logging)
add_subdirectory(Chimer.TestFramework)
add_subdirectory(Chimer.IO)

if (${CHIMER_TESTING})
  add_subdirectory(Chimer.TestFramework.Tests)
endif()
