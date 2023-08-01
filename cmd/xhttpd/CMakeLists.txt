cmake_minimum_required(VERSION 3.20)

project(xhttpd)

file(GLOB SOURCES "x_httpd_*.c")

SET(CMAKE_CXX_FLAGS "-O2")
SET(CMAKE_C_FLAGS "-O2")

set(BUILD_SHARED_LIBS OFF)
# set(CMAKE_EXE_LINKER_FLAGS "-static")

if (APPLE)
    add_compile_definitions(KQUEUE)
else()
    add_compile_definitions(EPOLL)
endif()

add_compile_definitions(_FORTIFY_SOURCE=2)
add_compile_definitions(_GNU_SOURCE)

add_executable(xhttpd ${SOURCES})

target_link_libraries(xhttpd PUBLIC x)
