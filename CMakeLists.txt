cmake_minimum_required(VERSION 3.20)

project(MIMO LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(mimo
    firmware/src/main.cpp
)

enable_testing()

add_test(NAME mimo_startup COMMAND mimo)
