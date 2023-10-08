#-
# $Copyright$
#

get_property(ARCH_NAME GLOBAL PROPERTY ARCH_NAME)

add_subdirectory(FreeRTOS)
add_subdirectory(printf)
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${ARCH_NAME})
    add_subdirectory(${ARCH_NAME})
endif()

