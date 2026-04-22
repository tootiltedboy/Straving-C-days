cmake_minimum_required(VERSION 3.22)
project(Chess CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Chess-build")

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_executable(Chess
        ${SOURCE_DIR}/main.cpp
        ${SOURCE_DIR}/MoveValidator.cpp
        ${SOURCE_DIR}/CheckValidator.cpp
        ${SOURCE_DIR}/MoveValidator.h
        ${SOURCE_DIR}/CheckValidator.h
)
