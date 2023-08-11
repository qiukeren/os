cmake_minimum_required(VERSION 3.20)

set(CMAKE_SYSTEM_NAME Linux)
# set(CMAKE_SYSTEM_PROCESSOR aarch64)

include(crosstools.cmake)

prepare_crosstool()

# set(CROSSTOOL_NAME "${XOS_BUILD_TARGET}-linux-musl-cross")
# message("build crosstools/${CROSSTOOL_NAME}")
# message("build crosstools/${CROSSTOOL_NAME}.tgz")
# message(
#     "build ${CMAKE_SOURCE_DIR}/crosstools/${CROSSTOOL_NAME}/bin/${XOS_BUILD_TARGET}-linux-musl-gcc"
# )
# set(CMAKE_C_COMPILER
#     "${CMAKE_SOURCE_DIR}/crosstools/${CROSSTOOL_NAME}/bin/${XOS_BUILD_TARGET}-linux-musl-gcc"
# )
# set(CMAKE_CXX_COMPILER
#     "${CMAKE_SOURCE_DIR}/crosstools/${CROSSTOOL_NAME}/bin/${XOS_BUILD_TARGET}-linux-musl-g++"
# )


# set(CMAKE_SYSROOT /home/devel/rasp-pi-rootfs)
# set(CMAKE_STAGING_PREFIX /home/devel/stage)

set(tools /root/osc/crosstools/riscv64-linux-musl-cross)
set(CMAKE_C_COMPILER ${tools}/bin/riscv64-linux-musl-gcc)
set(CMAKE_CXX_COMPILER ${tools}/bin/riscv64-linux-musl-g++)

# set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)


# set(CMAKE_SYSTEM_NAME Linux) set(CMAKE_SYSTEM_PROCESSOR x86_64)

# set(CMAKE_SYSROOT /opt/x86_64-linux-musl/x86_64-linux-musl/sys-root/)
# set(CMAKE_INSTALL_PREFIX $ENV{prefix})

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_RELEASE} -O2 -Wall")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} -O2 -Wall")

if(CMAKE_BUILD_TYPE MATCHES Debug)
    message("Debug build.")
    add_compile_definitions(DEBUG_ROOT="./test")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    message("Release build.")
    add_compile_definitions(DEBUG_ROOT="")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_RELEASE} -s")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} -s")
else()
    message(FATAL_ERROR "Some other build type.")
endif()

enable_testing()

include(GoogleTest)
# gtest_discover_tests(libs/x)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project(xos)

include_directories(
    xos
    PRIVATE
    libs/googletest/googletest
    libs/log
    libs/sqlite
    libs/x
    libs/xconf
    libs/xdb
    libs/httplib
    libs/zlib
    libs/linenoise
    libs/httplib)

# add_custom_target( c_build COMMAND ./configure WORKING_DIRECTORY musl COMMAND
# make WORKING_DIRECTORY musl )

# set_property(TARGET c PROPERTY IMPORTED_LOCATION "musl/lib/libc.so")
# link_directories("musl/lib/")

add_subdirectory(libs/googletest)
add_subdirectory(libs/log)
add_subdirectory(libs/linenoise)
# add_subdirectory(libs/sqlite)
add_subdirectory(libs/zlib)
add_subdirectory(libs/ini)
add_subdirectory(libs/x)
# add_subdirectory(libs/xconf) add_subdirectory(libs/xdb)

add_subdirectory(cmd/editor)

add_subdirectory(cmd/xpm)
add_subdirectory(cmd/xhttpd)
add_subdirectory(cmd/shell)
add_subdirectory(cmd/unnpk)

add_subdirectory(cmd/init)
add_subdirectory(cmd/xinit)
add_subdirectory(cmd/mgetty)
add_subdirectory(cmd/getty)
add_subdirectory(cmd/tgetty)
