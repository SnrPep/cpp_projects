cmake_minimum_required(VERSION 3.26)
project(Cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(Cpp main.cpp
        class.h
        myclass.cpp
        myclass.h)
