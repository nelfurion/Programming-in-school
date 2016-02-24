cmake_minimum_required(VERSION 2.6)

project(tail)

include_directories(./)

set(HEADER_FILES ./dynamic_array.h)

add_executable(tail tail.c)