cmake_minimum_required(VERSION 3.10)

project(
  coding-library
  VERSION 1.0.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(
  ${PROJECT_NAME} INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

add_subdirectory(src)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
option(TESTING_ENABLED "Enable testing" ON)

if(${TESTING_ENABLED})
  enable_testing()
  add_subdirectory(test)
endif()

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME "coding-library")
set(CPACK_PACKAGE_VENDOR "Jonas 'HAUBOJO' Haubold")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A simple C++ library for coding")
set(CPACK_PACKAGE_HOMEPAGE_URL
    "https://github.com/Honigkuchen/the-coding-library")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Jonas 'HAUBOJO' Haubold")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libfmt-dev, libgtest-dev")
set(CPACK_PACKAGE_FILE_NAME
    "${CPACK_PACKAGE_NAME}-cpp${CMAKE_CXX_STANDARD}-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_PROCESSOR}"
)
include(CPack)
