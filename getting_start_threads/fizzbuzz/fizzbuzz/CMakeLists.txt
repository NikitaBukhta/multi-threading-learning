cmake_minimum_required(VERSION 3.0.0)

set(
    LIB_NAME
    fizz_buzz_lib
)

set(
    SRC
    src/fizz_buzz.cpp
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