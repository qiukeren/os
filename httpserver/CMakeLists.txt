cmake_minimum_required(VERSION 3.20)

include_directories(../libs/httplib)

add_executable(httpserver httpserver.c)


if (APPLE)
    add_compile_definitions(KQUEUE)
else ()
    add_compile_definitions(EPOLL)
endif ()

target_link_libraries(httpserver)

