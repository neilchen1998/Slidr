find_library(PROFILER_LIB profiler REQUIRED)

add_executable(solverbenchmark solverbenchmark.cc)

target_link_libraries(solverbenchmark PRIVATE solver_library fmt::fmt)
