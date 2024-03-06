cmake_minimum_required(VERSION 3.24)
project(CoordinatesEx)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CoordinatesEx main.cpp CoordinatesInterface.h
        CoordinatesPZ90.cpp
        CoordinatesPZ90.h
        CoordinatesSK42.cpp
        CoordinatesSK42.h
        CoordinatesPZ90UnitTest.cpp
        CoordinatesSK42UnitTest.cpp
        CoordinatesTranslation.cpp
        CoordinatesTranslation.h
        CoordinatesTranslationUnitTest.cpp
        CoordinatesWGS84.cpp
        CoordinatesWGS84.h
)

target_link_libraries(CoordinatesEx gtest gmock pthread)

