#-
# $Copyright$
#
cmake_minimum_required(VERSION 2.8)
project(phisch)

get_property(DSP_ROOT GLOBAL PROPERTY DSP_ROOT)
message(STATUS "Building libdsp at ${DSP_ROOT}")

#*******************************************************************************
# Digital Signal Processing (DSP) Library
#*******************************************************************************
set(TARGET_NAME dsp)
set(TARGET_SRC
    BitReversal.cpp
    SinCosLut.cpp
)
add_library(${TARGET_NAME} ${TARGET_SRC})

#*******************************************************************************
# Testcases
#*******************************************************************************
if (GMOCK_FOUND)
    add_subdirectory(testcases)
endif(GMOCK_FOUND)
