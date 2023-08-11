cmake_minimum_required(VERSION 3.20)

project(x)

file(GLOB SOURCES "ini.c")

add_library(ini SHARED ${SOURCES})

add_library(ini_static STATIC ${SOURCES})

# file(GLOB SOURCESCPP "test_*.cpp")

# add_executable(test_ini ${SOURCESCPP})
# target_link_libraries(test_ini gtest gtest_main ini)
# gtest_discover_tests(test_ini)