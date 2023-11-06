if ("${TARGET_MCU}" STREQUAL stm32f767)
    add_executable(hal_st.robot)

    target_include_directories(hal_st.robot PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/..>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
    )

    target_sources(hal_st.robot PRIVATE
        Main.cpp
    )

    target_link_libraries(hal_st.robot PRIVATE
        services.util
        hal_st.instantiations
    )

    halst_target_default_linker_scripts(hal_st.robot)
    halst_target_default_init(hal_st.robot)

    emil_generate_artifacts(TARGET hal_st.robot LST MAP BIN HEX)
endif()