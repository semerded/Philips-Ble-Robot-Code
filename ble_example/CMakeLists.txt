if ("${TARGET_MCU}" STREQUAL stm32wb55)
    add_executable(robot.ble_example)

    target_include_directories(robot.ble_example PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/..>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
    )

    add_version_header_dependency(robot.ble_example robot.version)

    target_sources(robot.ble_example PRIVATE
        Main.cpp
    )

    target_link_libraries(robot.ble_example PRIVATE
        services.util
        hal_st.instantiations
        hal_st.ble_middleware
        robot_services
    )

    halst_target_default_linker_scripts(robot.ble_example)
    halst_target_default_init(robot.ble_example)

    emil_generate_artifacts(TARGET robot.ble_example LST MAP BIN HEX)
endif()