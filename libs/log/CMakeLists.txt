cmake_minimum_required(VERSION 3.20)

project(log)

add_library(log log.c)

target_include_directories(log PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
