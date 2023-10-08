#-
# $Copyright$
#
cmake_minimum_required(VERSION 2.8)
project(phisch)

get_property(GPIO_ROOT GLOBAL PROPERTY GPIO_ROOT)
message(STATUS "Building libgpio at ${GPIO_ROOT}")

#*******************************************************************************
# GPIO Library
#*******************************************************************************

#*******************************************************************************
# Testcases
#*******************************************************************************
if (GMOCK_FOUND)
    MESSAGE(STATUS "Building libgpio Testcases")
    add_subdirectory(testcases)
    target_link_libraries(${GPIO_LIB}
        gmock
    )
endif(GMOCK_FOUND)
