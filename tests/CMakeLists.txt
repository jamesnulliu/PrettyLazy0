# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${PROJECT_SOURCE_DIR}/src/*.cpp)
# Exclude main.cpp from the sources
list(FILTER SOURCES EXCLUDE REGEX ".*main.cpp$")

# Set the output path for the plazy examples
string(
    CONCAT PLAZY_EXAMPLE_OUTPUT_PATH
    ${PROJECT_SOURCE_DIR}/bin-tests/plazyExamples/
    ${CMAKE_BUILD_TYPE}/
    ${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR}/
)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${PLAZY_EXAMPLE_OUTPUT_PATH})
# Add the examples executables
add_executable(LexerExample ${SOURCES} "./Examples/Lexer_main.cpp")
add_executable(LoggerExample ${SOURCES} "./Examples/Logger_main.cpp")
add_executable(SplitExample ${SOURCES} "./Examples/Split_main.cpp")

# Set the output path for the plazy experiments
string(
    CONCAT PLAZY_EXPERIMENT_OUTPUT_PATH
    ${PROJECT_SOURCE_DIR}/bin-tests/plazyExperiments/
    ${CMAKE_BUILD_TYPE}/
    ${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR}/
)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${PLAZY_EXPERIMENT_OUTPUT_PATH})
# Add the experiments executables
add_executable(Exp01_RecognizeIdent ${SOURCES} "./Experiments/Exp01_RecognizeIdent_main.cpp")