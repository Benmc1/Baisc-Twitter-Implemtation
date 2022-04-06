cmake_minimum_required(VERSION 3.21)
project(COMP10050 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(COMP10050
        main.c
        main.h)
