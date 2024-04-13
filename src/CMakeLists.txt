file(GLOB MATH_HEADER_LIST CONFIGURE_DEPENDS "${8_PUZZLE_SOURCE_DIR}/include/math/*.hpp")

add_library(math_library mathlib.cc ${MATH_HEADER_LIST})

target_include_directories(math_library PUBLIC ../include)

target_compile_features(math_library PRIVATE cxx_std_20)  # requires C++20 for concept