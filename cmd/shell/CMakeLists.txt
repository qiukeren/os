cmake_minimum_required(VERSION 3.20)

add_executable(shell ui.c)

target_link_libraries(shell LINK_PUBLIC linenoise log)

