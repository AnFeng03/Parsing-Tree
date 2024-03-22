cmake_minimum_required(VERSION 3.26)
project(P2 C)

set(CMAKE_C_STANDARD 99)


set(CMAKE_C_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Werror -pedantic)
set(CMAKE_VERBOSE_MAKEFILE ON)


add_executable(P2 main.c
        rdp.c
        rdp.h
        tdp.c
        stack.c
        stack.h
        tdp.h
        tree.c
        tree.h
        queue.c
        queue.h
)
