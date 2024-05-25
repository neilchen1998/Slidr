# cmake requirements
cmake_minimum_required(VERSION 3.14)

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

    # exports compile commands
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    # compiler flags
    add_compile_options(-Wall -Wextra -pedantic -O3 -pg)

    # linker flags
    add_link_options(-pg)

    # uses CTest
    # NOTE: this needs to be done in the main CMakeLists
    include(CTest)

    # debug flag
    # set(DEBUG "1")
    # add_definitions(-DDEBUG=${DEBUG})

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

# the compiled library code
add_subdirectory(src)

# the executable code
add_subdirectory(apps)

# checks if we are in the main CMakeLists
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
    add_subdirectory(tests)
endif()