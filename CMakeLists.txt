# @Path: PrettyLazy0/CMakeLists.txt

# Minimum required CMake version
cmake_minimum_required(VERSION 3.21)

# Project name
project(PrettyLazy0 VERSION 0.1)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set defaut build type to Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DRELEASE_BUILD)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG_BUILD)
endif()

if(MSVC)
    # Set different compile options for Release and Debug modes
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi")
    # MSVC compiler-specific options
    add_compile_options(/permissive- /Zc:forScope)
else()
    # Set different compile options for Release and Debug modes
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
endif()

# [SUBDIRECTORIES] >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
# Yutils Library -----------------------------------------------------------------------------------
option(SHARED_YUTILS "Build Yutils as a shared library" OFF)
if (SHARED_YUTILS)
    # Set BUILD_SHARED_LIBS to ON to build Yutils as a shared library
    set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libs for Yutils" FORCE)
    # Build Yutils as a shared library
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/Yutils)
else()
    # Set BUILD_SHARED_LIBS to OFF to build Yutils as a shared library
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libs for Yutils" FORCE)
    # Build Yutils as a static library
    add_subdirectory(vendor/Yutils)
endif()
# src ----------------------------------------------------------------------------------------------
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
# tests --------------------------------------------------------------------------------------------
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
# [SUBDIRECTORIES] <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
