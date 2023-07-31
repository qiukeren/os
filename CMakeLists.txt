cmake_minimum_required(VERSION 3.20)

IF (NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug)
ENDIF ()

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_RELEASE} -O2 -Wall")
SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} -O2 -Wall")

IF (CMAKE_BUILD_TYPE MATCHES Debug)
    message("Debug build.")
ELSEIF (CMAKE_BUILD_TYPE MATCHES Release)
    message("Release build.")
    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_RELEASE} -s")
    SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} -s")
ELSE ()
    message("Some other build type.")
ENDIF ()


#add_custom_target(
#        c_build
#        COMMAND "./configure" "--prefix=${CMAKE_CURRENT_SOURCE_DIR}/musl" "--ldso=${CMAKE_CURRENT_SOURCE_DIR}/x86_64-linux-musl-cross/x86_64-linux-musl/lib/ld-musl-x86_64.so.1"
#        WORKING_DIRECTORY musl
#        COMMAND make
#        WORKING_DIRECTORY musl
#)
#
#set(CMAKE_LIBRARY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/musl/lib)
#set(LIBRARY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/musl/lib)
#
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/x86_64-linux-musl-cross/x86_64-linux-musl/include)
#
#link_libraries(${CMAKE_CURRENT_SOURCE_DIR}/musl/lib)
#
## Without that flag CMake is not able to pass test compilation check
#set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
#set(BAREMETAL_ARM_TOOLCHAIN_PATH ${CMAKE_CURRENT_SOURCE_DIR}/x86_64-linux-musl-cross/bin/)
#
#set(CMAKE_AR ${BAREMETAL_ARM_TOOLCHAIN_PATH}x86_64-linux-musl-ar)
#set(CMAKE_ASM_COMPILER ${BAREMETAL_ARM_TOOLCHAIN_PATH}x86_64-linux-musl-gcc)
#set(CMAKE_C_COMPILER ${BAREMETAL_ARM_TOOLCHAIN_PATH}x86_64-linux-musl-gcc)
#set(CMAKE_CXX_COMPILER ${BAREMETAL_ARM_TOOLCHAIN_PATH}x86_64-linux-musl-g++)
#set(CMAKE_LINKER ${BAREMETAL_ARM_TOOLCHAIN_PATH}x86_64-linux-musl-ld)
#set(CMAKE_OBJCOPY ${BAREMETAL_ARM_TOOLCHAIN_PATH}x86_64-linux-musl-objcopy)
#set(CMAKE_RANLIB ${BAREMETAL_ARM_TOOLCHAIN_PATH}x86_64-linux-musl-ranlib)
#set(CMAKE_SIZE ${BAREMETAL_ARM_TOOLCHAIN_PATH}x86_64-linux-musl-size)
#set(CMAKE_STRIP ${BAREMETAL_ARM_TOOLCHAIN_PATH}x86_64-linux-musl-strip)
#
#
#set(CMAKE_C_FLAGS "-Wno-psabi --specs=${CMAKE_CURRENT_SOURCE_DIR}/musl/lib/musl-gcc.specs -fdata-sections -ffunction-sections -Wl,--gc-sections" CACHE INTERNAL "")
#set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fno-exceptions" CACHE INTERNAL "")
#
#set(CMAKE_C_FLAGS_DEBUG "-Os -g" CACHE INTERNAL "")
#set(CMAKE_C_FLAGS_RELEASE "-Os -DNDEBUG" CACHE INTERNAL "")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}" CACHE INTERNAL "")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}" CACHE INTERNAL "")
#
#set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
#set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
#set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)


set(CMAKE_C_STANDARD 11)

project(xos)

#add_custom_target(
#        c_build
#        COMMAND ./configure
#        WORKING_DIRECTORY musl
#        COMMAND make
#        WORKING_DIRECTORY musl
#)

#set_property(TARGET c PROPERTY IMPORTED_LOCATION "musl/lib/libc.so")
#link_directories("musl/lib/")

add_subdirectory(libs/log)
add_subdirectory(libs/linenoise)
add_subdirectory(libs/sqlite)
add_subdirectory(libs/x)
add_subdirectory(libs/xdb)
add_subdirectory(libs/test)
add_subdirectory(httpserver)
add_subdirectory(editor)
add_subdirectory(init)
add_subdirectory(getty)
add_subdirectory(shell)
add_subdirectory(zlib)
add_subdirectory(unnpk)
