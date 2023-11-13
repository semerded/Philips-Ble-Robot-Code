add_library(robot_interfaces INTERFACE)

target_include_directories(robot_interfaces INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/..>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_sources(robot_interfaces PRIVATE
    CarControl.hpp
    MotorShieldControllerDc.hpp
    PwmDriver.hpp
    RobotServiceGattServer.hpp
    ShiftRegisterDriver.hpp
)

target_link_libraries(robot_interfaces INTERFACE
    hal.interfaces
)
