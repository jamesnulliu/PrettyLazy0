# Minimum required CMake version
cmake_minimum_required(VERSION 3.21)

# Project name
project(PrettyLazy0)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Source files
file(GLOB_RECURSE SOURCES src/*.cpp)

# Add executable with the project name
add_executable(${PROJECT_NAME}.out ${SOURCES})

# Set different compile options for Release and Debug modes
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-g")