cmake_minimum_required(VERSION 3.10)
project(RISCV_Olympiad_Challenge VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCES
    src/main.cpp
    src/Shape.cpp
    src/ShapeFactory.cpp
    src/Circle.cpp
    src/Square.cpp
    src/Rectangle.cpp
    # Uncomment to enable Triangle
    # src/Triangle.cpp
)

add_executable(describe_object ${SOURCES})
