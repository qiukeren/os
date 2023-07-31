cmake_minimum_required(VERSION 3.20)

project(xpm)

file(GLOB SOURCES "xpm_*.c")

include_directories(../../libs/x ../../libs/yaml/include)

SET(CMAKE_CXX_FLAGS "-O2")
SET(CMAKE_C_FLAGS "-O2")

set(BUILD_SHARED_LIBS OFF)
# set(CMAKE_EXE_LINKER_FLAGS "-static")

add_compile_definitions(_FORTIFY_SOURCE=2)
add_compile_definitions(_GNU_SOURCE)

add_executable(xpm ${SOURCES})

add_executable(test_xpm test_xpm_yaml.c)

target_link_libraries(xpm PUBLIC x yaml)

target_link_libraries(test_xpm PUBLIC x yaml)
