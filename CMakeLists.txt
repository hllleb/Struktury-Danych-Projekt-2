cmake_minimum_required(VERSION 3.30)
project(project2)

set(CMAKE_CXX_STANDARD 20)

add_executable(project2 main.cpp
        IPriorityQueue.h
        ArrayPriorityQueue.h)
