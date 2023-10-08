#-
# $Copyright$
#
cmake_minimum_required(VERSION 2.8)
project(phisch)

set(PRINTF_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set_property(GLOBAL PROPERTY PRINTF_ROOT ${PRINTF_ROOT})

get_property(PRINTF_ROOT GLOBAL PROPERTY PRINTF_ROOT)
message(STATUS "Building libprintf at ${PRINTF_ROOT}")

#*******************************************************************************
# Command Line Interface (CLI) Library
#*******************************************************************************
include_directories("${PRINTF_ROOT}")

set(TARGET_LIB "tpf")
set(TARGET_LIB_SOURCES
    printf.c
)
add_library(${TARGET_LIB} ${TARGET_LIB_SOURCES})
