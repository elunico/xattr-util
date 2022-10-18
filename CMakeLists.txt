cmake_minimum_required(VERSION 3.16)
project(xattr_util C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "-g -Og -DDEBUG")

add_executable(main main.c subproc.h subproc.c split.c split.h)
