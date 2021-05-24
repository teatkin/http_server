cmake_minimum_required(VERSION 3.19)
project(http_server C)

set(CMAKE_C_STANDARD 11)

file(GLOB SOURCES src/*.c)

add_executable(http_server ${SOURCES})