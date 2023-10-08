#-
# $Copyright$
#
cmake_minimum_required(VERSION 2.8)
project(phisch)

set(PROJECT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

message(STATUS "Project Root: ${PROJECT_ROOT}")
message(STATUS "System Type: ${CMAKE_SYSTEM_NAME}")
message(STATUS "System Processor: ${CMAKE_SYSTEM_PROCESSOR}")

###############################################################################
# Set up generic compile flags. If we're on a 'Generic', i.e. embedded system,
# we need the CMAKE_SYSTEM_PROCESSOR variable set via the Toolchain file.
###############################################################################
if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Generic")
    if (NOT DEFINED CMAKE_SYSTEM_PROCESSOR)
        message(FATAL_ERROR "CMAKE_SYSTEM_PROCESSOR not defined!")
    endif()
endif()

if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Generic")
    set(ARCH_NAME "${CMAKE_SYSTEM_PROCESSOR}")
else()
    set(ARCH_NAME "${CMAKE_SYSTEM_NAME}")
endif()
set_property(GLOBAL PROPERTY ARCH_NAME ${ARCH_NAME})

set(IPC_ENV "FreeRTOS")
set_property(GLOBAL PROPERTY IPC_ENV ${IPC_ENV})

###############################################################################
# Include Search Paths for project
###############################################################################
if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Generic")
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/compat)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/contrib/FreeRTOS/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/contrib/FreeRTOS/${ARCH_NAME})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/contrib/hxplay/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/contrib/hxplay/mp3/pub)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/contrib/PetitFAT/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/contrib/printf)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/contrib/STM32F4)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/contrib/STM32F4/CMSIS/Include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/contrib/STM32F4/CMSIS/ST/STM32F4xx/Include)

###############################################################################
# If we're on an embedded system, include a CMake File that sets up the
# architecture specific flags for the Compiler.
###############################################################################
if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Generic")
    include(${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR}.cflags)
endif()

add_definitions("-Wall")
add_definitions("-Werror")
add_definitions("-Wextra")
add_definitions("-g")
add_definitions("-Os")
add_definitions("-DWITH_PROFILING")

###############################################################################
# Set up the environment for the Phisch.Org libraries
###############################################################################
if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Generic")
    add_definitions("-DADC_ENV=${CMAKE_SYSTEM_PROCESSOR}")
    add_definitions("-DBLOCKDEV_ENV=SDCard")
    add_definitions("-DDMA_ENV=${CMAKE_SYSTEM_PROCESSOR}")
    add_definitions("-DGPIO_ENV=${CMAKE_SYSTEM_PROCESSOR}")
    add_definitions("-DIPC_ENV=FreeRTOS")
    add_definitions("-DPCM_ENV=${CMAKE_SYSTEM_PROCESSOR}")
    add_definitions("-DSPI_ENV=${CMAKE_SYSTEM_PROCESSOR}")
    add_definitions("-DTIMER_ENV=${CMAKE_SYSTEM_PROCESSOR}")
    add_definitions("-DUART_ENV=${CMAKE_SYSTEM_PROCESSOR}")

    if ("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "STM32F4")
        get_property(CMSIS_ROOT GLOBAL PROPERTY CMSIS_ROOT)

        include_directories(${CMSIS_ROOT}/Include)
        include_directories(${CMSIS_ROOT}/ST/STM32F4xx/Include)

        add_definitions("-DCORTEX_M4")
        add_definitions("-DSTM32F4XX")
        add_definitions("-DUSE_FULL_ASSERT")
    endif()
else()
    add_definitions("-DBLOCKDEV_ENV=File")
    add_definitions("-DGPIO_ENV=Lpt")
    add_definitions("-DLPT_ENV=${CMAKE_SYSTEM_NAME}")
    add_definitions("-DPCM_ENV=${CMAKE_SYSTEM_NAME}")
    add_definitions("-DUART_ENV=${CMAKE_SYSTEM_NAME}")
endif()


###############################################################################
# Environment for library directories
###############################################################################

###############################################################################
# Include Library subdirectories
###############################################################################
add_subdirectory(compat)
add_subdirectory(contrib)
add_subdirectory(devices)
add_subdirectory(dsp)
add_subdirectory(gpio)
add_subdirectory(ipc)
if (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "Generic")
    add_subdirectory(lpt)
endif()
add_subdirectory(tasks)
add_subdirectory(uart)

###############################################################################
# Project Tasks
###############################################################################
set(PROJECT_TASKS
    tasks/Heartbeat.cpp
)

###############################################################################
# Actually build the target binary
###############################################################################
set(TARGET_NAME firmware)
set(TARGET_ELF ${TARGET_NAME}.elf)
set(TARGET_BIN ${TARGET_NAME}.bin)
set(TARGET_SRC
    main${ARCH_NAME}.cpp
    FreeRTOSCallback.cpp
    CompatStdCpp.cpp
    ${PROJECT_TASKS}
)
add_executable(${TARGET_ELF}
    ${TARGET_SRC}
)
target_link_libraries(${TARGET_ELF}
    devices
    dsp
    FreeRTOS
    ipc
    tasks
    uart
)

if (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "Generic")
    target_link_libraries(${TARGET_ELF}
        lpt
    )
endif()

###############################################################################
# If we're on an embedded system, include a CMake File that defines how the
# flashable binary image is built
###############################################################################
if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Generic")
    include(${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR}.cmake)
    set(GDBINIT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/gdbinit-${CMAKE_SYSTEM_PROCESSOR}.tpl)
else()
    find_package(Threads REQUIRED)
    target_link_libraries(${TARGET_ELF}
        ${CMAKE_THREAD_LIBS_INIT}
    )
    set(GDBINIT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/gdbinit.tpl)
endif()
configure_file(${GDBINIT_FILE} ${CMAKE_CURRENT_BINARY_DIR}/.gdbinit)
