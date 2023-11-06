add_executable(hal_st.robot Main.cpp)

emil_build_for(hal_st.blink_nucleo144 TARGET_MCU_VENDOR st PREREQUISITE_BOOL HALST_BUILD_EXAMPLES)

target_compile_definitions(hal_st.blink_nucleo144 PUBLIC
    NUCLEO=Nucleo144Ui
)

target_link_libraries(hal_st.blink_nucleo144 PRIVATE
    services.util
    hal_st.instantiations
)

halst_target_default_linker_scripts(hal_st.blink_nucleo144)
halst_target_default_init(hal_st.blink_nucleo144)

emil_generate_artifacts(TARGET hal_st.blink_nucleo144 LST MAP BIN HEX)