cmake_minimum_required(VERSION 3.10)

project(coding-library VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)
add_subdirectory(src)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
option(TESTING_ENABLED "Enable testing" ON)

if(${TESTING_ENABLED})
  enable_testing()
  add_subdirectory(test)
endif()
