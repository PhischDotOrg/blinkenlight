include_directories(${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Device/ST/STM32F4xx/Include)

add_definitions("-Wno-error=misleading-indentation")

set(TARGET_NAME cmsis)
set(TARGET_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
)
add_library(${TARGET_NAME} ${TARGET_SRC})

set(TARGET_NAME     startup)
set(TARGET_OBJ      ${TARGET_NAME}.o)
set(TARGET_SRC      ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/ST/STM32F4xx/Source/Templates/gcc_ride7/startup_stm32f4xx.s)
set(TARGET_LDSCRIPT stm32f4_flash.ld)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_OBJ}
    COMMAND ${CMAKE_C_COMPILER} ARGS
      -c -o ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_OBJ}
      -nostartfiles -mcpu=cortex-m4 -mthumb
      ${TARGET_SRC}
    DEPENDS ${TARGET_SRC}
)

add_custom_target(${TARGET_NAME}
    COMMAND true
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_OBJ}
)

# Required for Generic_STM32F4.cmake
set_property(GLOBAL PROPERTY STARTUP_OBJ ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_OBJ})
set_property(GLOBAL PROPERTY STARTUP_LDSCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_LDSCRIPT})
set_property(GLOBAL PROPERTY STARTUP_TARGET ${TARGET_NAME})
