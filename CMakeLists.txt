# Minimum required CMake version
cmake_minimum_required(VERSION 3.21)

# Project name
project(PrettyLazy0 VERSION 0.1)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(./include)

# Source files
file(GLOB_RECURSE SOURCES src/*.cpp)
# Exclude main.cpp from the sources
list(FILTER SOURCES EXCLUDE REGEX ".*main.cpp$")

# Set output directory: bin/{Release, Debug}/{win,linux,mac}_{x86, x64}
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR})

# Add executable with the project name
add_executable(plazy ${SOURCES} "src/main.cpp")

# [To be Tested] Visual Studio Specific Options
if(MSVC)
    # Set different compile options for Release and Debug modes
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi")

    # MSVC compiler-specific options
    add_compile_options(/permissive- /Zc:forScope)

# g++/clang++ specific options
else()
    # Set different compile options for Release and Debug modes
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    
endif()

# Copy the executable to the bin/current directory
# add_custom_command(TARGET plazy POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:plazy> ${PROJECT_SOURCE_DIR}/bin/current/
# )