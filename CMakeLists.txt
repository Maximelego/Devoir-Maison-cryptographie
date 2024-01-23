cmake_minimum_required(VERSION 3.27)
project(projet C)

set(CMAKE_C_STANDARD 23)

add_executable(projet main.c
        utils/random_utils.c
        utils/include/random_utils.h
        constants.h)
