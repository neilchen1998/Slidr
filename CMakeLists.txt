# cmake requirements
cmake_minimum_required(VERSION 3.5...4.0)

project(
    8-Puzzle
    VERSION 0.1
    DESCRIPTION "Solve 8 Puzzle problem"
    LANGUAGES CXX
)

# checks if we are in the main CMakeLists
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    # ensures -std=c++xx instead of -std=g++xx for protability purposes
    set(CMAKE_CXX_EXTENSIONS OFF)

    # compiler flags
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-Wall -Wextra -pedantic -g3 -fsanitize=address,undefined)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "Test" OR CMAKE_BUILD_TYPE STREQUAL "Bench")
        add_compile_options(-Wall -Wextra -pedantic -O3)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Gprof")
        add_compile_options(-Wall -pg -O0)
    endif()

    # linker flags
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_link_options(-g3 -fsanitize=address,undefined)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Gprof")
        add_link_options(-pg)
    endif()

    # uses CTest
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

# all required packages
find_package(Boost REQUIRED)
find_package(Boost COMPONENTS program_options REQUIRED) # boost::program_options
# find_library(PROFILER_LIB profiler REQUIRED)

# all required packages
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG        11.2.0)
FetchContent_MakeAvailable(fmt)

# the compiled library code
add_subdirectory(src)

# the executable code
add_subdirectory(apps)

# checks if we are in the main CMakeLists
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING AND CMAKE_BUILD_TYPE STREQUAL "Test")
    add_subdirectory(tests)
elseif((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING AND CMAKE_BUILD_TYPE STREQUAL "Benchmark")
    add_subdirectory(benchmarks)
elseif((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING AND CMAKE_BUILD_TYPE STREQUAL "Gprof")
    add_subdirectory(gprof)
endif()
