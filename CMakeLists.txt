cmake_minimum_required(VERSION 3.24)
project(CoordinatesEx)

set(CMAKE_CXX_STANDARD 14)

add_executable(CoordinatesEx main.cpp CoordinatesInterface.cpp CoordinatesInterface.h CoordinatesTransition.cpp CoordinatesTransition.h)
