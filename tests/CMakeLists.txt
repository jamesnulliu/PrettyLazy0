cmake_minimum_required(VERSION 3.21)

Project(YutilsTests)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/Yutils/include
)

# Source files
file(GLOB_RECURSE SOURCES ./*.cpp ../src/*.cpp)
# Exclude main.cpp from the sources
list(FILTER SOURCES EXCLUDE REGEX ".*main.cpp$")

# Set the output path for the plazy examples
string(
    CONCAT PLAZY_EXAMPLE_OUTPUT_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/bin/
    plazyExamples/ ${CMAKE_BUILD_TYPE}/
    ${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR}/
)

# Link the Yutils library
link_libraries(Yutils)
# Or link to the library manually
# > link_libraries(/path/to/lib)

# Whether Yutils is built as shared library
# @see PrettyLazy0/CMakeLists.txt:option(SHARED_YUTILS "Build Yutils as a shared library" ...)
if(SHARED_YUTILS)
    # Define YUTILS_IMPORT when using the DLL, critical for windows
    add_compile_definitions(YUTILS_IMPORT)
endif()

# Set the output path for the plazy examples
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${PLAZY_EXAMPLE_OUTPUT_PATH})

# Add the examples executables
add_executable(LexerExample ${SOURCES} "./Examples/Lexer_main.cpp")

# Set the output path for the plazy experiments
string(
    CONCAT PLAZY_EXPERIMENT_OUTPUT_PATH
    ${PROJECT_SOURCE_DIR}/bin/plazyExperiments/
    ${CMAKE_BUILD_TYPE}/
    ${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR}/
)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${PLAZY_EXPERIMENT_OUTPUT_PATH})

# Add the experiments executables
add_executable(exp01 ${SOURCES} "./Experiments/exp01-recognize-identifier_main.cpp")
add_executable(exp02 ${SOURCES} "./Experiments/exp02-analyze-morphology_main.cpp")
add_executable(exp03 ${SOURCES} "./Experiments/exp03-grammar-analyze_main.cpp")
add_executable(exp06 ${SOURCES} "./Experiments/exp06-optimize_main.cpp")