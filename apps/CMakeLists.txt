add_executable(app app.cc)

apply_compiler_flags(app)

# Link required libraries
target_link_libraries(app PRIVATE solver_library prompt_library)
