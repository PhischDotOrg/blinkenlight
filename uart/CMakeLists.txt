#-
# $Copyright$
#
cmake_minimum_required(VERSION 2.8)
project(phisch)

get_property(UART_ROOT GLOBAL PROPERTY UART_ROOT)
message(STATUS "Building libuart at ${UART_ROOT}")

get_property(PRINTF_ROOT GLOBAL PROPERTY PRINTF_ROOT)

#*******************************************************************************
# UART Library
#*******************************************************************************
include_directories("${PRINTF_ROOT}")
include_directories("${UART_ROOT}/include")

set(TARGET_LIB "uart")
if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Generic")
    set(TARGET_LIB_SOURCES
        UartAccess${CMAKE_SYSTEM_PROCESSOR}.cpp
    )
    if ("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "STM32F4")
        get_property(CMSIS_ROOT GLOBAL PROPERTY CMSIS_ROOT)
        get_property(PROJECT_ROOT GLOBAL PROPERTY PROJECT_ROOT)

        include_directories(${CMSIS_ROOT}/Include)
        include_directories(${CMSIS_ROOT}/ST/STM32F4xx/Include)
    endif()
else()
    set(TARGET_LIB_SOURCES
        UartAccess${CMAKE_SYSTEM_NAME}.cpp
    )
endif()

add_library(${TARGET_LIB} ${TARGET_LIB_SOURCES})
target_link_libraries(${TARGET_LIB}
    tpf
)

#*******************************************************************************
# Testcases
#*******************************************************************************
if (GMOCK_FOUND)
    MESSAGE(STATUS "Building libuart Testcases")
    add_subdirectory(testcases)
    target_link_libraries(${TARGET_LIB}
        gmock
    )
endif(GMOCK_FOUND)
