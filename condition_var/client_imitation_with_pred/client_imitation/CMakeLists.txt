cmake_minimum_required(VERSION 3.0.0)

set(
    LIB_NAME
    client_lib
)

set(
    SRC
    src/client.cpp
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