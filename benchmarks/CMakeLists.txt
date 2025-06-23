FetchContent_Declare(
  nanobench
  GIT_REPOSITORY https://github.com/martinus/nanobench.git
  GIT_TAG v4.3.10)
FetchContent_MakeAvailable(nanobench)

add_executable(mathbenchmarklib mathbenchmarklib.cc)
add_executable(nodebenchmarklib nodebenchmarklib.cc)

target_compile_features(mathbenchmarklib PRIVATE cxx_std_20)
target_compile_features(nodebenchmarklib PRIVATE cxx_std_20)

target_link_libraries(mathbenchmarklib PRIVATE nanobench math_library Boost::boost)
target_link_libraries(nodebenchmarklib PRIVATE nanobench node_library)
