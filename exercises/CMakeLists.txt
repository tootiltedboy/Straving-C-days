cmake_minimum_required(VERSION 3.14)
project(Starving-C-days)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
        Chess-build/main.cpp
        Chess-build/CheckValidator.cpp
        Chess-build/MoveValidator.cpp
)

set(HEADERS
        Chess-build/CheckValidator.h
        Chess-build/MoveValidator.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
endif()

if (APPLE)
    message(STATUS "Building for macOS")
elseif (WIN32)
    message(STATUS "Building for Windows")
else ()
    message(STATUS "Building for Linux")
endif()

