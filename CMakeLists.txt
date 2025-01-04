# CMakeLists.txt

cmake_minimum_required(VERSION 3.28)
project(AdventOfCode2024 LANGUAGES CXX)

# Enable C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

# Export compile commands for IDEs and tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Prevent in-source builds
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "In-source builds not allowed. Please create a separate build directory.")
endif()

# -------------------- Set FetchContent Base Directory --------------------
# Define the base directory for FetchContent to download external libraries
if(WIN32)
  set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/external/windows")
elseif(UNIX)
  set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/external/linux")
endif()

if(UNIX AND NOT APPLE)
  # Disable Wayland support if not needed
  set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "Disable Wayland support in GLFW" FORCE)
  set(GLFW_BUILD_X11 ON CACHE BOOL "Enable X11 support in GLFW" FORCE)
endif()

# Include FetchContent module
include(FetchContent)

# -------------------- Fetch GLFW --------------------
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        latest
)

# Fetch GLFW
FetchContent_MakeAvailable(glfw)

# -------------------- Fetch Glad --------------------
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG        v0.1.34
)

# Fetch Glad
FetchContent_MakeAvailable(glad)

# -------------------- Fetch Dear ImGui --------------------
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG        v1.89.6  # Use the latest stable tag
)

# Fetch ImGui
FetchContent_GetProperties(imgui)
if(NOT imgui_POPULATED)
  FetchContent_Populate(imgui)
  
  # Add ImGui as a library
  add_library(imgui
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
  )
  
  target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends)
  
  # Define IMGUI_IMPL_OPENGL_LOADER_GLAD to use Glad
  target_compile_definitions(imgui PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)
  
  # Link ImGui with GLFW and OpenGL
  target_link_libraries(imgui PUBLIC glfw OpenGL::GL glad)
endif()

# -------------------- Find OpenGL --------------------
find_package(OpenGL REQUIRED)

# -------------------- Add Executable --------------------
add_executable(AdventOfCode2024)

# Add your source files and modules
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
    src/days/Day19.cppm
    src/days/Day20.cppm
    src/rendering/maingui.cppm
)

# Add main.cpp
target_sources(AdventOfCode2024 PRIVATE
  src/main.cpp
)

# Include directories
target_include_directories(AdventOfCode2024 PRIVATE src)

# -------------------- Link External Libraries --------------------
target_link_libraries(AdventOfCode2024 PRIVATE
  imgui
  glfw
  OpenGL::GL
  glad
)

# -------------------- Platform-Specific Settings --------------------

if(UNIX AND NOT APPLE)
  # Linux-specific settings
  # Link X11 libraries required by GLFW
  find_package(X11 REQUIRED)
  target_link_libraries(AdventOfCode2024 PRIVATE X11::X11)
endif()

# -------------------- Precompiled Headers (Optional) --------------------
# If you use precompiled headers, you can set them up here
# target_precompile_headers(AdventOfCode2024 PRIVATE src/pch.h)

# -------------------- C++ Modules Support --------------------
# Ensure that all modules are properly linked if needed
# This depends on how your modules are set up
