cmake_minimum_required(VERSION 3.20)

project(tgetty)

SET(CMAKE_CXX_FLAGS "-O2 -Wall -Werror")
SET(CMAKE_C_FLAGS "-O2 -Wall")

set(CMAKE_EXE_LINKER_FLAGS "-static")

add_compile_definitions(_FORTIFY_SOURCE=2)
add_compile_definitions(_GNU_SOURCE)


add_executable(tgetty getty.c)

target_link_libraries(tgetty PUBLIC c)

