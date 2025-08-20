add_executable(app app.cc)

# Link required libraries
target_link_libraries(app PRIVATE solver_library prompt_library)
