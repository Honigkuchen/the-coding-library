cmake_minimum_required(VERSION 3.10)

project(coding-library VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)
add_subdirectory(src)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
option(TESTING_ENABLED "Enable testing" ON)

if(${TESTING_ENABLED})
  enable_testing()

  # Download and unpack googletest at configure time
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
  )

  # Prevent overriding the parent project's compiler/linker
  # settings on Windows
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
  
  add_subdirectory(test)
endif()
