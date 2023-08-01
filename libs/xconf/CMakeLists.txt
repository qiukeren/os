cmake_minimum_required(VERSION 3.20)

project(xconf)

file(GLOB SOURCES "x_*.c")

file(GLOB SOURCESCPP "test_*.cpp")

add_library(xconf SHARED ${SOURCES})

add_library(xconf_static STATIC ${SOURCES})

