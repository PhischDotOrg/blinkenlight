#-
# $Copyright$
#
cmake_minimum_required(VERSION 2.8)
project(phisch)

get_property(DEVICES_ROOT GLOBAL PROPERTY DEVICES_ROOT)
message(STATUS "Building libdevices at ${DEVICES_ROOT}")

#*******************************************************************************
# Devices Library
#*******************************************************************************
set(TARGET_NAME devices)
set(TARGET_SRC
    FlashViaSTM32F4.cpp
    PwrViaSTM32F4.cpp
    RccViaSTM32F4.cpp
    ScbViaSTM32F4.cpp
)
if (TARGET_SRC)
    add_library(${TARGET_NAME} ${TARGET_SRC})
endif()

#*******************************************************************************
# Testcases
#*******************************************************************************
if (GMOCK_FOUND AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/testcases)
    add_subdirectory(testcases)
endif()
