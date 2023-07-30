cmake_minimum_required(VERSION 3.20)

project(user)

add_library(user user.c)

target_include_directories(user PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
