cmake_minimum_required(VERSION 3.23)
project(xattr_util C)

set(CMAKE_C_STANDARD 17)

add_executable(xattr_util
        main.c subproc.h subproc.c)
