cmake_minimum_required(VERSION 3.20)

project(x)

file(GLOB SOURCES "x_*.c")

add_library(x SHARED ${SOURCES})

add_library(x_static STATIC ${SOURCES})

target_include_directories(log PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
