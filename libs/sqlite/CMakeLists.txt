cmake_minimum_required(VERSION 3.20)

project(sqlite)

add_library(sqlite SHARED sqlite3.c)

add_executable(sqlite3_shell shell.c)

target_link_libraries(sqlite dl pthread)
target_link_libraries(sqlite3_shell PUBLIC sqlite)