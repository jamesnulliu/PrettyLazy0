# @Path: PrettyLazy0/CMakeLists.txt

# Minimum required CMake version
cmake_minimum_required(VERSION 3.21)

# Project name
project(PrettyLazy0 VERSION 0.1)

# Whether to build Yutils as a shared library
option(SHARED_YUTILS "Build Yutils as a shared library" OFF)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set defaut build type to Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
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

# [Subdirectories] >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
# Yutils Library
if (SHARED_YUTILS)
    # Store the original value of BUILD_SHARED_LIBS
    set(ORIGINAL_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})
    # Set BUILD_SHARED_LIBS to ON to build Yutils as a shared library
    set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libs for Yutils" FORCE)
    # Build Yutils as a shared library
    add_subdirectory(vendor/Yutils)
    # Restore the original value of BUILD_SHARED_LIBS
    set(BUILD_SHARED_LIBS ${ORIGINAL_BUILD_SHARED_LIBS} CACHE BOOL "Restore oritinal value")
else()
    # Store the original value of BUILD_SHARED_LIBS
    set(ORIGINAL_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})
    # Set BUILD_SHARED_LIBS to OFF to build Yutils as a shared library
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libs for Yutils" FORCE)
    # Build Yutils as a static library
    add_subdirectory(vendor/Yutils)
    # Restore the original value of BUILD_SHARED_LIBS
    set(BUILD_SHARED_LIBS ${ORIGINAL_BUILD_SHARED_LIBS} CACHE BOOL "Restore oritinal value")
endif()
# src
add_subdirectory(src)
# tests
add_subdirectory(tests)
# [Subdirectories] <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
