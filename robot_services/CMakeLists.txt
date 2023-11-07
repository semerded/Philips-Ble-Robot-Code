add_library(robot_services STATIC EXCLUDE_FROM_ALL)

target_include_directories(robot_services PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/..>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_sources(robot_services PRIVATE
    ShiftRegisterDriver.cpp
    ShiftRegisterDriver.hpp
)

target_link_libraries(robot_services PUBLIC
    hal.interfaces
)

if (ROBOT_BUILD_TESTS)
    add_subdirectory(test)
endif()