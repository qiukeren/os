cmake_minimum_required(VERSION 3.20)

project(x)

file(GLOB SOURCES "*.c")

add_library(pbfile SHARED ${SOURCES})

add_library(pbfile_static STATIC ${SOURCES})
