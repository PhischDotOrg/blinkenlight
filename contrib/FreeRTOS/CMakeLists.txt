get_property(ARCH_NAME GLOBAL PROPERTY ARCH_NAME)

###############################################################################
# If we're building on a "Generic" system, assume that this build is for an
# embedded processor. Chose the FreeRTOS 'port.c' file based on the CPU type.
#
# If we're building for a different system, assume we're a POSIX-compliant
# operating system and use the POSIX 'port.c'.
###############################################################################
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/FreeRTOS)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${ARCH_NAME})

if("${ARCH_NAME}" STREQUAL "Linux")
    remove_definitions("-Werror")
endif()

set(TARGET_NAME FreeRTOS)
set(TARGET_SRC
    croutine.c
    list.c
    queue.c
    tasks.c
    timers.c
    heap_4.c
    ${ARCH_NAME}/port.c
)
add_library(${TARGET_NAME} ${TARGET_SRC})
