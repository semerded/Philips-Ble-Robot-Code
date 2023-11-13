add_executable(robot_services_test)
emil_add_test(robot_services_test)

target_sources(robot_services_test PRIVATE
    TestShiftRegisterDriver.cpp
    TestMotorShieldControllerDc.cpp
    TestBasicCarControl.cpp
    TestBleUi.cpp
    TestCarControlToGattCharacteristic.cpp
    
)

target_link_libraries(robot_services_test PUBLIC
    gmock_main
    robot_services
    hal.interfaces_test_doubles
    services.ble_test_doubles
    infra.timer_test_helper

)
