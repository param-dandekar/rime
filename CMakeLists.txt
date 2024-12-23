cmake_minimum_required(VERSION 3.10)

project(SRISC)
set(CMAKE_CXX_STANDARD 17)

# Ensure compilation database is created
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Ensure the Debug build type is set
set(CMAKE_BUILD_TYPE Debug)

# Override the Debug flags to include -ggdb
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb -O0")
set(CMAKE_C_FLAGS_DEBUG "-ggdb -O0")

# Automatically collect all .cpp files in the src/ directory
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Add executable with all found source files
add_executable(processor ${SOURCES})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Set include directories for headers
target_include_directories(processor PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
)

# message(STATUS "CMAKE_SOURCE_DIR is: ${CMAKE_SOURCE_DIR}")
message("CFLAGS_DEBUG: ${CMAKE_C_FLAGS_DEBUG}")
message("CXXFLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
