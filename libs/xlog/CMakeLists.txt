cmake_minimum_required(VERSION 3.20)

project(xlog)

file(GLOB SOURCES "xlog.c")

add_library(xlog SHARED ${SOURCES})

add_library(xlog_static STATIC ${SOURCES})
