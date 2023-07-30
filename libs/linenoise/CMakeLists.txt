cmake_minimum_required(VERSION 3.20)

project(linenoise)

add_library(linenoise linenoise.c)

target_include_directories(linenoise PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
