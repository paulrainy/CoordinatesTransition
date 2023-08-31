cmake_minimum_required(VERSION 3.24)
project(CoordinatesEx)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(CoordinatesEx main.cpp CoordinatesInterface.h
        CoordinatesPZ90.cpp
        CoordinatesPZ90.h
        CoordinatesSK42.cpp
        CoordinatesSK42.h
        CoordinatesPZ90UnitTest.cpp
        CoordinatesSK42UnitTest.cpp
)

target_link_libraries(CoordinatesEx gtest gmock pthread)

