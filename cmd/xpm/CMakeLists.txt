cmake_minimum_required(VERSION 3.20)

project(xpm)

include_directories(../../libs/x)

SET(CMAKE_CXX_FLAGS "-O2")
SET(CMAKE_C_FLAGS "-O2")

set(BUILD_SHARED_LIBS OFF)
# set(CMAKE_EXE_LINKER_FLAGS "-static")

add_compile_definitions(_FORTIFY_SOURCE=2)
add_compile_definitions(_GNU_SOURCE)

add_executable(xpm main.c xpm_xinit.c)

target_link_libraries(xpm PUBLIC x)
