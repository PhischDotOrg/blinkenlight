#-
# $Copyright$
#
cmake_minimum_required(VERSION 2.8)
project(phisch)

get_property(LPT_ROOT GLOBAL PROPERTY LPT_ROOT)
message(STATUS "Building liblpt at ${LPT_ROOT}")

#*******************************************************************************
# LPT Library
#*******************************************************************************
add_definitions("-D__STDC_FORMAT_MACROS")
set(LPT_LIB "lpt")
set(LPT_LIB_SOURCES
    LptAccess${CMAKE_SYSTEM_NAME}.cpp
)
add_library(${LPT_LIB} ${LPT_LIB_SOURCES})
