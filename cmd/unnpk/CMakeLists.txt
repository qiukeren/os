cmake_minimum_required(VERSION 3.20)

project(unnpk)

SET(CMAKE_CXX_FLAGS "-O2")
SET(CMAKE_C_FLAGS "-O2")

set(BUILD_SHARED_LIBS OFF)
# set(CMAKE_EXE_LINKER_FLAGS "-static")

add_compile_definitions(_FORTIFY_SOURCE=2)
add_compile_definitions(_GNU_SOURCE)


add_executable(unnpk unnpk.c)

target_link_libraries(unnpk PUBLIC zlib)

file(GLOB SOURCESCPP "test_*.cpp")
add_executable(test_unnpk ${SOURCESCPP})
target_link_libraries(test_unnpk gtest gtest_main)
gtest_discover_tests(test_unnpk)