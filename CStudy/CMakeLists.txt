cmake_minimum_required(VERSION 3.22)
project(CStudy)

set(CMAKE_CXX_STANDARD 14)

include_directories(CStudy)

add_executable(CStudy
        CStudy/C1.c
        CStudy/C1.h
        CStudy/main.cpp)
