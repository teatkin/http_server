cmake_minimum_required(VERSION 3.19)
project(http_server LANGUAGES C VERSION 0.0.1)

set(CMAKE_C_STANDARD 11)

file(GLOB SOURCES src/*.c)
include_directories(inc/)

add_executable(http_server ${SOURCES})