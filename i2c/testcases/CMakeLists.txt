#-
# $Copyright$
#
cmake_minimum_required(VERSION 2.8)
project(phisch)

#*******************************************************************************
# Testcases Requirements
#*******************************************************************************
get_property(GMOCK_FOUND GLOBAL PROPERTY GMOCK_FOUND)
if(NOT GMOCK_FOUND)
    message(FATAL_ERROR "The libiic Testcases cannot be build without GMock!")
endif(NOT GMOCK_FOUND)

get_property(GMOCK_ROOT GLOBAL PROPERTY GMOCK_ROOT)
include_directories("${GMOCK_ROOT}/include")

get_property(GTEST_ROOT GLOBAL PROPERTY GTEST_ROOT)
include_directories("${GTEST_ROOT}/include")

get_property(I2C_ROOT GLOBAL PROPERTY I2C_ROOT)
include_directories("${I2C_ROOT}")
include_directories("${I2C_ROOT}/include")

get_property(GPIO_ROOT GLOBAL PROPERTY GPIO_ROOT)
include_directories("${GPIO_ROOT}/include")

#*******************************************************************************
# Testcases
#*******************************************************************************
set(TC_SOURCES
    test_I2cDevice.cpp
    test_I2cBusViaGpio.cpp
    test_I2cTransfer.cpp
)

#*******************************************************************************
# Test Executor
#*******************************************************************************
set(TARGET_EXE test_libs_i2c)
add_executable(${TARGET_EXE} main.cpp ${TC_SOURCES})
target_link_libraries(${TARGET_EXE}
    gmock
    iic
)

#*******************************************************************************
# Configure CTest and the CDash Drop Location
#*******************************************************************************
add_test(NAME libiic COMMAND ${TARGET_EXE})

