add_library(robot_services STATIC EXCLUDE_FROM_ALL)

target_include_directories(robot_services PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/..>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_sources(robot_services PRIVATE
    RobotServiceDefinition.cpp
    RobotServiceDefinition.hpp
    ShiftRegisterDriverImpl.cpp
    ShiftRegisterDriverImpl.hpp
    MotorShieldControllerDcImpl.cpp
    MotorShieldControllerDcImpl.hpp
    BasicCarControl.cpp
    BasicCarControl.hpp
    BleUi.hpp
    BleUi.cpp
)

target_link_libraries(robot_services PUBLIC
    robot_interfaces
    hal.interfaces
    infra.util
)

if (ROBOT_BUILD_TESTS)
    add_subdirectory(test_doubles)
    add_subdirectory(test)
endif()