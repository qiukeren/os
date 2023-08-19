cmake_minimum_required(VERSION 3.20)

project(x)

file(GLOB SOURCES "bench.c")

add_library(bench SHARED ${SOURCES})

add_library(bench_static STATIC ${SOURCES})

add_executable(bench_example example.c)

target_link_libraries(bench_example PUBLIC bench_static)

