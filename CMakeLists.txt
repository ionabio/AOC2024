# CMakeLists.txt

cmake_minimum_required(VERSION 3.28)
project(AdventOfCode2024 LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

add_executable(AdventOfCode2024)
target_sources(AdventOfCode2024 PRIVATE
FILE_SET all_my_modules TYPE CXX_MODULES FILES
  src/days/Day1.cppm
  src/days/Day2.cppm)
target_sources(AdventOfCode2024 PRIVATE
  src/main.cpp
)
target_include_directories(AdventOfCode2024 PRIVATE src)
