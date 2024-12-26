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

### Emulator

set(RIME rime)

set(RIME_SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(RIME_INC_DIR ${CMAKE_SOURCE_DIR}/include)

# Automatically collect all .cpp files in the src/ directory
file(GLOB RIME_SOURCES "${RIME_SRC_DIR}/*.cpp")

# Add executable with all found source files
add_executable(${RIME} ${RIME_SOURCES})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Set include directories for headers
target_include_directories(${RIME} PRIVATE
    ${RIME_INC_DIR}
)

# message(STATUS "CMAKE_SOURCE_DIR is: ${CMAKE_SOURCE_DIR}")
message("CFLAGS_DEBUG: ${CMAKE_C_FLAGS_DEBUG}")
message("CXXFLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")

### Assembler

set(ASSM_SRC_DIR src/rime)
set(ASSM_INC_DIR include/rime)

# Parser and Lexer files
set(PARSER parser)
set(LEXER lexer)

set(PARSER_SRC ${ASSM_SRC_DIR}/${PARSER}.y)
set(PARSER_OUT ${CMAKE_BINARY_DIR}/${PARSER}.c)
set(PARSER_HEADER ${CMAKE_BINARY_DIR}/${PARSER}.h)

set(LEXER_SRC ${ASSM_SRC_DIR}/${LEXER}.l)
set(LEXER_OUT ${CMAKE_BINARY_DIR}/${LEXER}.yy.c)

set(ASSEMBLER_MAIN ${ASSM_SRC_DIR}/main.cpp)

# Enable Bison and Flex
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

# Bison target
BISON_TARGET(${PARSER} ${PARSER_SRC} ${PARSER_OUT} DEFINES_FILE ${PARSER_HEADER})

# Flex target
FLEX_TARGET(${LEXER} ${LEXER_SRC} ${LEXER_OUT})

# Add the generated files to the project
ADD_FLEX_BISON_DEPENDENCY(${LEXER} ${PARSER})

# Include directories
include_directories(${ASSM_INC_DIR} ${CMAKE_BINARY_DIR})

# Executable
add_executable(rc ${PARSER_OUT} ${LEXER_OUT} ${ASSEMBLER_MAIN})

# Link libraries
target_link_libraries(rc fl)
