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
  src/utils/Files.cppm
  src/days/Day1.cppm
  src/days/Day2.cppm
  src/days/Day3.cppm
  src/days/Day4.cppm
  src/days/Day5.cppm
  src/days/Day6.cppm
  src/days/Day7.cppm
  src/days/Day8.cppm
  src/days/Day9.cppm
  src/days/Day10.cppm
  src/days/Day11.cppm
  src/days/Day12.cppm
  src/days/Day13.cppm
  src/days/Day14.cppm
  src/days/Day15.cppm
  src/days/Day16.cppm
  src/days/Day17.cppm
  src/days/Day18.cppm
  )
target_sources(AdventOfCode2024 PRIVATE
  src/main.cpp
)
target_include_directories(AdventOfCode2024 PRIVATE src)
