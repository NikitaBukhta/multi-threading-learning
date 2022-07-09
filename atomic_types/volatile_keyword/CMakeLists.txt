#--------------------------- STANDART CONFIGURATION ---------------------------#

cmake_minimum_required(VERSION 3.0.0)

project(volatile_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)
set(CMAKE_BUILD_TYPE debug)

#-------------------------------- SET EXECUTABLE -------------------------------#

set(
    EXE
    $CACHE{CMAKE_PROJECT_NAME}
)
set(
    SRC
    main.cpp
)

add_executable(
    ${EXE}
    ${SRC}
)