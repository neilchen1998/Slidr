add_executable(app app.cc)

# required libraries
target_link_libraries(app PRIVATE ${Boost_LIBRARIES} ${PROFILER_LIB} solver_library prompt_library)
