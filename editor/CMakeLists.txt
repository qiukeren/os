cmake_minimum_required(VERSION 3.20)

include_directories(../log/)

add_executable(editor editor.c)

target_link_libraries(editor LINK_PUBLIC log)

