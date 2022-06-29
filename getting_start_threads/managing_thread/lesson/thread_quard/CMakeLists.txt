cmake_minimum_required(VERSION 3.0.0)

set(
    LIB_NAME
    thread_quard_lib
)

set(
    SRC
    src/thread_quard.cpp
)

set(
    HEADERS_DIR
    include
)

add_library(
    ${LIB_NAME}
    ${SRC}
)

target_include_directories(
    ${LIB_NAME}
    PUBLIC
    ${HEADERS_DIR}
)