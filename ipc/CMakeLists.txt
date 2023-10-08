#-
# $Copyright$
#
cmake_minimum_required(VERSION 2.8)
project(phisch)

get_property(IPC_ROOT GLOBAL PROPERTY IPC_ROOT)
get_property(IPC_ENV GLOBAL PROPERTY IPC_ENV)
message(STATUS "Building libipc at ${IPC_ROOT} for ${IPC_ENV} Environment")

#*******************************************************************************
# IPC Library
#*******************************************************************************
set(TARGET_LIB "ipc")
set(TARGET_LIB_SOURCES
    Mutex${IPC_ENV}.cpp
)
add_library(${TARGET_LIB} ${TARGET_LIB_SOURCES})

if ("${IPC_ENV}" STREQUAL "FreeRTOS")
    target_link_libraries(${TARGET_LIB}
        FreeRTOS
    )
endif()

#*******************************************************************************
# Testcases
#*******************************************************************************
if (GMOCK_FOUND)
    add_subdirectory(testcases)
endif(GMOCK_FOUND)
