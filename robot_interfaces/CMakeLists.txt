add_library(robot_interfaces INTERFACE)

target_include_directories(robot_interfaces INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/..>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_sources(robot_interfaces PRIVATE
    PwmDriver.hpp
    ShiftRegisterDriver.hpp
    MotorShieldControllerDc.hpp
)

target_link_libraries(robot_interfaces INTERFACE
    hal.interfaces
)
