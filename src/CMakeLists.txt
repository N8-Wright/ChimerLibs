add_subdirectory(Chimer.Logging)
add_subdirectory(Chimer.TestFramework)

if (${CHIMER_TESTING})
  add_subdirectory(Chimer.TestFramework.Tests)
endif()
