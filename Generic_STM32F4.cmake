get_property(ARCH_DIR GLOBAL PROPERTY ARCH_DIR)

get_property(STARTUP_OBJ GLOBAL PROPERTY STARTUP_OBJ)
get_property(STARTUP_LDSCRIPT GLOBAL PROPERTY STARTUP_LDSCRIPT)
get_property(STARTUP_TARGET GLOBAL PROPERTY STARTUP_TARGET)
get_property(CMSIS_ROOT GLOBAL PROPERTY CMSIS_ROOT)

#
# Firmware image
#
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${STARTUP_OBJ} -T ${STARTUP_LDSCRIPT}")

target_link_libraries(${TARGET_ELF}
    cmsis
)
add_dependencies(${TARGET_ELF}
    ${STARTUP_TARGET}
    ${STARTUP_LDSCRIPT}
)

add_custom_command(OUTPUT ${TARGET_BIN}
    COMMAND arm-none-eabi-objcopy   # FIXME Base on Toolchain file?
      ARGS -O binary ${TARGET_ELF} ${TARGET_BIN}
    DEPENDS ${TARGET_ELF}
)
add_custom_target(${TARGET_NAME} ALL true DEPENDS ${TARGET_BIN})

