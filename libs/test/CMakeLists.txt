cmake_minimum_required(VERSION 3.20)

project(test)

include_directories(../x)

add_executable(test_kernel_log test_kernel_log.c)

target_link_libraries(test_kernel_log PUBLIC x)
