cmake_minimum_required(VERSION 3.21)
project(COMP10050 C)

set(CMAKE_C_STANDARD 99)

add_executable(COMP10050
        main.c
        Users.c
        Users.h Delete.c Delete.h Structs.h Follow.c Follow.h Twt+News.c Twt+News.h)
