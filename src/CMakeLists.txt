# @Path: PrettyLazy0/src/CMakeLists.txt

# Minimum required CMake version
cmake_minimum_required(VERSION 3.21)

# PROJECT_NAME: plazy
Project(plazy)  

# Source files
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# Exclude main.cpp from the sources
list(FILTER SOURCES EXCLUDE REGEX ".*main.cpp$")

# Add executable with the project name
add_executable(${PROJECT_NAME} ${SOURCES} "./main.cpp")

# Set target include directories:
# - PrettyLazy0/include
# - PrettyLazy0/vendor/Yutils/include
target_include_directories(
    ${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/Yutils/include
)

# Link to Yutils library automatically
# @see PrettyLazy0/vendor/Yutils/src/CMakeLists.txt:add_library(${LIBRARY_NAME} ...)
target_link_libraries(${PROJECT_NAME} PRIVATE Yutils)
# Or link to the library manually
# > target_link_libraries(${PROJECT_NAME} PRIVATE /path/to/lib)

# Whether Yutils is built as shared library
# @see PrettyLazy0/CMakeLists.txt:option(SHARED_YUTILS "Build Yutils as a shared library" ...)
if (SHARED_YUTILS)
    # Define YUTILS_IMPORT when using the DLL, critical for windows
    target_compile_definitions(${PROJECT_NAME} PRIVATE YUTILS_IMPORT)
endif()

set_target_properties(
    plazy PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}/../bin/${CMAKE_BUILD_TYPE}/${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR}
)