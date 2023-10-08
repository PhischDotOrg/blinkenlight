#-
# $Copyright$
#
cmake_minimum_required(VERSION 2.8)
project(phisch)

get_property(SPI_ROOT GLOBAL PROPERTY SPI_ROOT)
message(STATUS "Building libspi at ${SPI_ROOT}")

#*******************************************************************************
# SPI Library
#*******************************************************************************

#*******************************************************************************
# Testcases
#*******************************************************************************
if (GMOCK_FOUND)
    MESSAGE(STATUS "Building libspi Testcases")
    add_subdirectory(testcases)
        target_link_libraries(${SPI_LIB}
        gmock
    )
endif(GMOCK_FOUND)
