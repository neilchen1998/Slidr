# The minimum cmake requirements
cmake_minimum_required(VERSION 3.5...4.0)

project(
    8-Puzzle
    VERSION 1.1
    DESCRIPTION "Solve 8 Puzzle problem"
    LANGUAGES CXX
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Check if we are in the main CMakeLists
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    # Ensure -std=c++xx instead of -std=g++xx for protability purposes
    set(CMAKE_CXX_EXTENSIONS OFF)

    # Set compiler flags
    if(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "Test" OR CMAKE_BUILD_TYPE STREQUAL "Benchmark")
        add_compile_options(-Wall -Wextra -pedantic -Wconversion -Wsign-conversion -O3 -ffast-math)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-Wall -Wextra -pedantic -g3 -fsanitize=address,undefined)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Gprof")
        add_compile_options(-pg)
    endif()

    # Set linker flags
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_link_options(-g3 -fsanitize=address,undefined)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Gprof")
        add_link_options(-pg)
    endif()

    # Use CTest
    # NOTE: this needs to be done in the main CMakeLists
    include(CTest)

    # Docs only available in the main app
    find_package(Doxygen)
    if(Doxygen_FOUND)
        add_subdirectory(docs)
    else()
        message(STATUS "Doxygen not found")
    endif()
endif()

# FetchContent helps grabbing repos during the configure step
# NOTE: available after CMake 3.11
include(FetchContent)

# all required packages (system)
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING AND CMAKE_BUILD_TYPE STREQUAL "Benchmark")
    find_package(Boost REQUIRED)
endif()

# Try to find the fmt library that is at least newer than 11.2.0 on the machine
find_package(fmt CONFIG 11.0.0 QUIET)
if (NOT fmt_FOUND)
    message(STATUS "fmt could not be found or version is too old, downloading via FetchContent...")
    # all required packages (will be downloaded automatically)
    FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG        11.2.0)
    FetchContent_MakeAvailable(fmt)
endif()

# The compiled library code
add_subdirectory(src)

# Check if we need to build the example
if (BUILD_EXAMPLES OR CMAKE_BUILD_TYPE STREQUAL "Release")
    # The executable code
    add_subdirectory(apps)
endif()

# Check if we are in the main CMakeLists
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING AND CMAKE_BUILD_TYPE STREQUAL "Test")
    add_subdirectory(tests)
elseif((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING AND CMAKE_BUILD_TYPE STREQUAL "Benchmark")
    add_subdirectory(benchmarks)
elseif((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING AND CMAKE_BUILD_TYPE STREQUAL "Gprof")
    add_subdirectory(gprof)
endif()
