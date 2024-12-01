# CMakeLists.txt

cmake_minimum_required(VERSION 3.24)
project(AdventOfCode2024 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable C++20 modules
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add source files
set(SOURCES
    src/main.cpp
    src/days/Day1.cppm
    # Add more modules as needed
)

# Create executable
add_executable(AdventOfCode2024 ${SOURCES})

# Include directories
target_include_directories(AdventOfCode2024 PRIVATE src)