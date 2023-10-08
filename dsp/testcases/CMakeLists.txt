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
    message(FATAL_ERROR "The libfatfs Testcases cannot be build without GMock!")
endif(NOT GMOCK_FOUND)

get_property(GMOCK_ROOT GLOBAL PROPERTY GMOCK_ROOT)
include_directories("${GMOCK_ROOT}/include")

get_property(GTEST_ROOT GLOBAL PROPERTY GTEST_ROOT)
include_directories("${GTEST_ROOT}/include")

get_property(KISSFFT_ROOT GLOBAL PROPERTY KISSFFT_ROOT)
include_directories("${KISSFFT_ROOT}")

set(FFTW_ROOT /opt)
include_directories("${FFTW_ROOT}/include")

if (HAVE_FFTW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/${FFTW_ROOT}/lib")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -L/${FFTW_ROOT}/lib")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -L/${FFTW_ROOT}/lib")
endif()

#*******************************************************************************
# Compile Environment
#*******************************************************************************

#*******************************************************************************
# Component Testcases
#*******************************************************************************
set(COMPONENTS
    BitReversal
    Complex
    ConstantQ
    Fft
    FilterChain
    Sine
    SinCos
    SinCosLibM
    TransformFilter
)

foreach(COMPONENT IN LISTS COMPONENTS)
    message(STATUS "Adding Tests for Component '${COMPONENT}'")

    set(COMPONENT_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../${COMPONENT}.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../${COMPONENT}.cpp
        test_${COMPONENT}.cpp
    )

    set(COMPONENT_TESTRUNNER dsp_${COMPONENT}_tests)

    add_executable(${COMPONENT_TESTRUNNER}
        ${COMPONENT_SOURCES}
    )
    target_link_libraries(${COMPONENT_TESTRUNNER}
        gmock
        gmock_main
    )

    if (${COMPONENT} STREQUAL "Fft")
        target_link_libraries(${COMPONENT_TESTRUNNER}
            dsp
            kissfft
        )
        if (HAVE_FFTW)
            target_link_libraries(${COMPONENT_TESTRUNNER}
                fftw3
            )
        endif()
    endif()

    add_test(NAME dsp_${COMPONENT} COMMAND ${COMPONENT_TESTRUNNER})
endforeach()
#
##*******************************************************************************
## Test Executor
##*******************************************************************************
#set(TC_SOURCES
#    test_SinCos.cpp
#    test_SinCosLibM.cpp
#    test_Sine.cpp
#)
#
#set(TARGET_EXE test_libs_dsp)
#add_executable(${TARGET_EXE} ${TC_SOURCES})
#target_link_libraries(${TARGET_EXE}
#    dsp
#    gmock
#    gmock_main
#    kissfft
#)
#
##*******************************************************************************
## Configure CTest and the CDash Drop Location
##*******************************************************************************
#add_test(NAME libdsp COMMAND ${TARGET_EXE})
