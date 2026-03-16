cmake_minimum_required(VERSION 3.24)
project(CoordinatesTransition VERSION 1.0)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include Directories
include_directories(include)

# Download and Setup GTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
)
# For Windows: set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Auxiliary Library
add_library(coord_lib STATIC
    src/CoordinateConverter.cpp
)

target_include_directories(coord_lib PUBLIC include)

# Test Runner Executable
add_executable(coord_tests
    tests/CoordinateTests.cpp
)

# Link Libraries
target_link_libraries(coord_tests PRIVATE coord_lib GTest::gtest GTest::gtest_main GTest::gmock)

# Enable testing
enable_testing()
add_test(NAME AllTests COMMAND coord_tests)
