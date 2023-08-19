cmake_minimum_required(VERSION 3.20)

project(xpm)

file(GLOB SOURCES "xpm_*.c")

SET(CMAKE_CXX_FLAGS "-O2")
SET(CMAKE_C_FLAGS "-O2")


add_compile_definitions(_FORTIFY_SOURCE=2)
add_compile_definitions(_GNU_SOURCE)

add_executable(xpm ${SOURCES})

target_link_libraries(xpm PUBLIC x)
