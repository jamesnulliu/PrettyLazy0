# Minimum required CMake version
cmake_minimum_required(VERSION 3.21)

# Project name
project(PrettyLazy0 VERSION 0.1)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Source files
file(GLOB_RECURSE SOURCES src/*.cpp)

# Set output directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# Add executable with the project name
add_executable(plazy ${SOURCES})

# [To be Tested] Visual Studio Specific Options
if(MSVC)
    # Set different compile options for Release and Debug modes
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi")

    # MSVC compiler-specific options
    add_compile_options(/permissive- /Zc:forScope)

    # Set the startup project to 'plazy' so that Visual Studio directly launches this project.
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT plazy)

    # Optional: Set debug working directory (useful for debugging with Visual Studio)
    set_property(TARGET plazy PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# g++/clang++ specific options
else()
    # Set different compile options for Release and Debug modes
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    
endif()