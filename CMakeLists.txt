cmake_minimum_required(VERSION 3.20)
project(DSAProject_Group58)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DSAProject_Group58
        src/parse.cpp src/parse.h
        src/main.cpp src/shellsort.cpp src/shellsort.h src/display.cpp src/display.h src/mergesort.cpp src/mergesort.h)

