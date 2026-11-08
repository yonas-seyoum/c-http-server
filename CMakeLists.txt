cmake_minimum_required(VERSION 3.20)

project(C_HTTP_Server LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSION OFF)

add_executable(server
    src/main.c
)
