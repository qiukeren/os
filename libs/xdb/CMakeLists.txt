cmake_minimum_required(VERSION 3.20)

project(xdb)

file(GLOB SOURCES "x_db_*.c")

add_library(xdb SHARED ${SOURCES})

add_library(xdb_static STATIC ${SOURCES})

include_directories(../sqlite)

include_directories(../x)

add_executable(test_x_db_user test_x_db_user.c)

target_link_libraries(test_x_db_user PUBLIC sqlite x)


