cmake_minimum_required(VERSION 3.20)

IF (NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug)
ENDIF ()


SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_RELEASE} -O2 -Wall")
SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} -O2 -Wall")

IF (CMAKE_BUILD_TYPE MATCHES Debug)
    message("Debug build.")
    add_compile_definitions(DEBUG_ROOT="./test")
ELSEIF (CMAKE_BUILD_TYPE MATCHES Release)
    message("Release build.")
    add_compile_definitions(DEBUG_ROOT="")
    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_RELEASE} -s")
    SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} -s")
ELSE ()
    message(FATAL_ERROR "Some other build type.")
ENDIF ()


enable_testing()

include(GoogleTest)
#gtest_discover_tests(libs/x)

set(CMAKE_C_STANDARD 11)

project(xos)

include_directories(xos PRIVATE
        libs/googletest/googletest
        libs/log
        libs/sqlite
        libs/x
        libs/xconf
        libs/xdb
        libs/httplib
        libs/zlib
        libs/linenoise
        libs/httplib
)

#add_custom_target(
#        c_build
#        COMMAND ./configure
#        WORKING_DIRECTORY musl
#        COMMAND make
#        WORKING_DIRECTORY musl
#)

#set_property(TARGET c PROPERTY IMPORTED_LOCATION "musl/lib/libc.so")
#link_directories("musl/lib/")

add_subdirectory(libs/googletest)
add_subdirectory(libs/log)
add_subdirectory(libs/linenoise)
add_subdirectory(libs/sqlite)
add_subdirectory(libs/zlib)
add_subdirectory(libs/ini)
add_subdirectory(libs/x)
add_subdirectory(libs/xconf)
add_subdirectory(libs/xdb)
add_subdirectory(editor)

add_subdirectory(cmd/xpm)
add_subdirectory(cmd/xhttpd)
add_subdirectory(shell)
add_subdirectory(unnpk)

if (LINUX)
    add_subdirectory(init)
    add_subdirectory(getty)
endif ()