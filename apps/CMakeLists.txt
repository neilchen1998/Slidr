add_executable(app app.cc)
target_compile_features(app PRIVATE cxx_std_20)

# required libraries
target_link_libraries(app PRIVATE ${Boost_LIBRARIES} ${PROFILER_LIB} solver_library prompt_library)
