#-
# $Copyright$
#

set(TARGET_NAME tasks)
set(TARGET_SRC
    Task.cpp
)

add_library(${TARGET_NAME} ${TARGET_SRC})
target_link_libraries(${TARGET_NAME}
    FreeRTOS
)
