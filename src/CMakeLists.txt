file(GLOB MATH_HEADER_LIST CONFIGURE_DEPENDS "${8_PUZZLE_SOURCE_DIR}/include/math/*.hpp")
file(GLOB PATTERN_HEADER_LIST CONFIGURE_DEPENDS "${8_PUZZLE_SOURCE_DIR}/include/pattern/*.hpp")
file(GLOB CONSTANTS_HEADER_LIST CONFIGURE_DEPENDS "${8_PUZZLE_SOURCE_DIR}/include/constants/*.hpp")
file(GLOB NODE_HEADER_LIST CONFIGURE_DEPENDS "${8_PUZZLE_SOURCE_DIR}/include/node/*.hpp")
file(GLOB SOLVER_HEADER_LIST CONFIGURE_DEPENDS "${8_PUZZLE_SOURCE_DIR}/include/solver/*.hpp")

add_library(math_library mathlib.cc ${MATH_HEADER_LIST})
add_library(pattern_library patternlib.cc ${PATTERN_HEADER_LIST})
add_library(constants_library constantslib.cc ${CONSTANTS_HEADER_LIST})
add_library(node_library nodelib.cc ${NODE_HEADER_LIST})
add_library(solver_library solverlib.cc ${SOLVER_HEADER_LIST})

target_include_directories(math_library PUBLIC ../include)
target_include_directories(pattern_library PUBLIC ../include)
target_include_directories(constants_library PUBLIC ../include)
target_include_directories(node_library PUBLIC ../include)
target_include_directories(solver_library PUBLIC ../include)

target_link_libraries(node_library PUBLIC math_library pattern_library constants_library)
target_link_libraries(solver_library PUBLIC node_library)

target_compile_features(math_library PUBLIC cxx_std_20)  # requires C++20 for concept
target_compile_features(pattern_library PUBLIC cxx_std_20)
target_compile_features(constants_library PUBLIC cxx_std_20)
target_compile_features(node_library PUBLIC cxx_std_20)
target_compile_features(solver_library PUBLIC cxx_std_20)
