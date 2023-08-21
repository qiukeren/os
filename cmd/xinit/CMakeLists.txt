cmake_minimum_required(VERSION 3.20)

project(xinit)

# set(BUILD_SHARED_LIBS OFF)
# set(CMAKE_EXE_LINKER_FLAGS "-static")

add_compile_definitions(_FORTIFY_SOURCE=2)
add_compile_definitions(_GNU_SOURCE)


add_executable(xinit xinit.c xinit_func.c)
target_link_libraries(xinit PUBLIC x_static xlog_static)


file(GLOB SOURCESCPP "test_*.cpp")
add_executable(test_xinit ${SOURCESCPP} xinit_func.c)
target_link_libraries(test_xinit gtest gtest_main x_static xlog_static)
gtest_discover_tests(test_xinit)
