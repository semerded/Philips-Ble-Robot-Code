cmake_minimum_required(VERSION 3.22.2)

project(robot VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)

add_subdirectory(amp-hal-st)
add_subdirectory(embedded_infra_lib)

emil_folderize_all_targets()

add_subdirectory(robot)
add_subdirectory(test)