#-
# $Copyright$
#
cmake_minimum_required(VERSION 2.8)
project(phisch)

get_property(I2C_ROOT GLOBAL PROPERTY I2C_ROOT)
message(STATUS "Building libiic at ${I2C_ROOT}")

#*******************************************************************************
# Compile Environment
#*******************************************************************************
add_definitions("-D__STDC_FORMAT_MACROS")

#*******************************************************************************
# I2C Library
#*******************************************************************************
set(IIC_LIB "iic")
set(IIC_LIB_SOURCES
    I2cBus${CMAKE_SYSTEM_NAME}.cpp
)
if(NOT ("${CMAKE_SYSTEM_NAME}" STREQUAL "Embedded"))
    set(IIC_LIB_SOURCES ${IIC_LIB_SOURCES} I2cTransfer.cpp)
endif()
add_library(${IIC_LIB} ${IIC_LIB_SOURCES})

#*******************************************************************************
# Testcases
#*******************************************************************************
if (GMOCK_FOUND)
    MESSAGE(STATUS "Building libiic Testcases")
    add_subdirectory(testcases)
    target_link_libraries(${IIC_LIB}
        gmock
    )
endif(GMOCK_FOUND)
