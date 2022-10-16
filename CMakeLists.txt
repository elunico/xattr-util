cmake_minimum_required(VERSION 3.16)
project(xattr_util C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "-g")

add_executable(xattr_util
        main.c subproc.h subproc.c)
