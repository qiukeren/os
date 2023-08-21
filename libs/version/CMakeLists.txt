cmake_minimum_required(VERSION 3.20)

project(version)

file(GLOB SOURCES "*.c")

add_executable(version ${SOURCES})

target_link_libraries(version PUBLIC sqlite)
