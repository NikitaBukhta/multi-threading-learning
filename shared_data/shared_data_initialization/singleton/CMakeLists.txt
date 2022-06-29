cmake_minimum_required(VERSION 3.0.0)

set(
    LIB_NAME
    singleton_lib
)

set(
    SRC
    src/singleton.cpp
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