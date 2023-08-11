cmake_minimum_required(VERSION 3.20)

project(init)


SET(CMAKE_CXX_FLAGS "-O2")
SET(CMAKE_C_FLAGS "-O2")

set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_compile_definitions(_FORTIFY_SOURCE=2)
add_compile_definitions(_GNU_SOURCE)


add_executable(init init.c init_func.c)

target_link_libraries(init PUBLIC log x_static)


file(GLOB SOURCESCPP "test_*.cpp")

# add_executable(test_init ${SOURCESCPP})
# target_link_libraries(test_init gtest gtest_main x_static)
# gtest_discover_tests(test_init)
