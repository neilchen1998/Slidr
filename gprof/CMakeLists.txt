add_executable(solverbenchmark solverbenchmark.cc)

target_link_libraries(solverbenchmark PRIVATE solver_library fmt::fmt)
