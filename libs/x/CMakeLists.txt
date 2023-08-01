cmake_minimum_required(VERSION 3.20)

project(x)

file(GLOB SOURCES "x_*.c")

file(GLOB SOURCESCPP "test_*.cpp")

add_library(x SHARED ${SOURCES})

add_library(x_static STATIC ${SOURCES})

add_executable(test_x_kernel_log test_x_kernel_log.cpp)
target_link_libraries(test_x_kernel_log gtest gtest_main)
gtest_discover_tests(test_x_kernel_log)

target_link_libraries(x PUBLIC sqlite)

