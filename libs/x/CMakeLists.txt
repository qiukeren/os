cmake_minimum_required(VERSION 3.20)

project(x)

file(GLOB SOURCES "x_*.c")

file(GLOB SOURCESCPP "test_*.cpp" "*/test_*.cpp")

add_library(x SHARED ${SOURCES})

add_library(x_static STATIC ${SOURCES})

#target_link_libraries(x PUBLIC sqlite)

# add_executable(test_cflag test_cflag.c)
# target_link_libraries(test_cflag x log_static)

if ("${XOS_BUILD_TARGET}" STREQUAL "")
    add_executable(test_libx ${SOURCESCPP})
    target_link_libraries(test_libx gtest gtest_main x xlog_static)
    gtest_discover_tests(test_libx)
endif ()