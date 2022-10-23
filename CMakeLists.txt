cmake_minimum_required(VERSION 3.21)
project(lab3c)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab3c main.cpp PCB.cpp PCB.hpp dialog.cpp dialog.hpp )

add_subdirectory(GTESTS)