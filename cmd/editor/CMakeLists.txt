cmake_minimum_required(VERSION 3.20)

add_executable(editor editor.c)

target_link_libraries(editor PUBLIC xlog_static)
