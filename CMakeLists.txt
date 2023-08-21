cmake_minimum_required(VERSION 3.20)

project(xos)

include(crosstools.cmake)

prepare_crosstool()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_RELEASE} -O2 -Wall")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} -O2 -Wall")


if(CMAKE_BUILD_TYPE MATCHES Debug)
    message("Debug build.")
    add_definitions(-DLOG_LEVEL=TRACE_LEVEL)
    add_compile_definitions(DEBUG_ROOT="./test")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    message("Release build.")
    add_compile_definitions(DEBUG_ROOT="")
#    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_RELEASE} -s")
#    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} -s")
else()
    message(FATAL_ERROR "Some other build type.")
endif()

enable_testing()

include(GoogleTest)
# gtest_discover_tests(libs/x)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)


include_directories(
    xos
    PRIVATE
    libs/googletest
    libs/xlog
    libs/sqlite
    libs/x
    libs/xconf
    libs/xdb
    libs/httplib
    libs/zlib
    libs/linenoise
)



add_subdirectory(libs/googletest)
add_subdirectory(libs/xlog)
add_subdirectory(libs/linenoise)
add_subdirectory(libs/sqlite)
add_subdirectory(libs/zlib)
add_subdirectory(libs/ini)
add_subdirectory(libs/x)
add_subdirectory(libs/version)

# add_subdirectory(libs/xconf) add_subdirectory(libs/xdb)

add_subdirectory(cmd/examples)

add_subdirectory(cmd/editor)
add_subdirectory(cmd/validation)
# add_subdirectory(cmd/xpm_pack_validation)
add_subdirectory(cmd/xpm)
add_subdirectory(cmd/xhttpd)
add_subdirectory(cmd/shell)
add_subdirectory(cmd/unnpk)

add_subdirectory(cmd/init)
add_subdirectory(cmd/xinit)
add_subdirectory(cmd/mgetty)
add_subdirectory(cmd/getty)
add_subdirectory(cmd/tgetty)
