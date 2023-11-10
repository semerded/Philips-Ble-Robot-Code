cmake_minimum_required(VERSION 3.24)

project(robot VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)

set(HALST_BUILD_EXAMPLES Off CACHE INTERNAL "")

option(CMAKE_COMPILE_WARNING_AS_ERROR "Enable warnings-as-error" On)
option(ROBOT_BUILD_TESTS "Enable build of the tests" On)

add_subdirectory(amp-embedded-infra-lib)
add_subdirectory(amp-hal-st)

if (ROBOT_BUILD_TESTS)
    include(CTest)
    emil_enable_testing()
endif()

add_version_header_target(robot.version)

add_subdirectory(robot_interfaces)
add_subdirectory(robot_services)
add_subdirectory(robot)
add_subdirectory(ble_example)

emil_exclude_directory_from_clang_format(amp-embedded-infra-lib)
emil_exclude_directory_from_clang_format(amp-hal-st)
emil_clangformat_directories(robot DIRECTORIES .)
emil_folderize_all_targets()
