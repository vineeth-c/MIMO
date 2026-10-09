cmake_minimum_required(VERSION 3.20)

project(MIMO LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# shared firmware logic
add_library(mimo_core
    firmware/src/MimoStateMachine.cpp
)

target_include_directories(mimo_core PUBLIC
    firmware/include
)

#MIMO simulator
add_executable(mimo
    firmware/src/main.cpp
)

target_link_libraries(mimo PRIVATE mimo_core)

# Automated tests
enable_testing()

add_test(
    NAME mimo_startup
    COMMAND mimo --smoke-test
)

set_tests_properties(mimo_startup PROPERTIES
    TIMEOUT 5
)

add_executable(test_state_machine
    tests/test_state_machine.cpp
)

target_link_libraries(test_state_machine PRIVATE mimo_core)

add_test(NAME state_machine COMMAND test_state_machine)

add_test(
    NAME event_loop
    COMMAND bash
        ${CMAKE_SOURCE_DIR}/tests/test_event_loop.sh
        $<TARGET_FILE:mimo>
        ${CMAKE_SOURCE_DIR}/tests/event_sequence.txt
)

set_tests_properties(event_loop PROPERTIES
    TIMEOUT 5
)