#-
# $Copyright$
#
cmake_minimum_required(VERSION 2.8)
project(phisch)

get_property(DSTRUCT_ROOT GLOBAL PROPERTY DSTRUCT_ROOT)
message(STATUS "Building libdstruct at ${DSTRUCT_ROOT}")

#*******************************************************************************
# Digital Signal Processing (DSP) Library
#*******************************************************************************
set(TARGET_NAME dstruct)
set(TARGET_SRC
    RingBuffer.cpp
)
add_library(${TARGET_NAME} ${TARGET_SRC})

#*******************************************************************************
# Testcases
#*******************************************************************************
if (GMOCK_FOUND)
    add_subdirectory(testcases)
endif(GMOCK_FOUND)
