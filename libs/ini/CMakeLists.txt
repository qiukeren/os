cmake_minimum_required(VERSION 3.20)

project(x)

file(GLOB SOURCES "ini.c")


add_library(ini SHARED ${SOURCES})

add_library(ini_static STATIC ${SOURCES})

add_executable(test_ini test_ini.c)

target_link_libraries(test_ini PUBLIC ini)

