cmake_minimum_required(VERSION 3.20)

project(x)

file(GLOB SOURCES "x_*.c")

include_directories(../log)
include_directories(../sqlite)

add_library(x SHARED ${SOURCES})

add_library(x_static STATIC ${SOURCES})


target_link_libraries(x PUBLIC sqlite)

