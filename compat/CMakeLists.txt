#-
# $Copyright$
#
cmake_minimum_required(VERSION 2.8)
project(phisch)

set(TARGET_NAME compatc)
set(TARGET_SRC
    strlen.c
)
add_library(${TARGET_NAME} ${TARGET_SRC})
