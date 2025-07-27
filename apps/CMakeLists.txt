add_executable(app app.cc)

# required libraries
target_link_libraries(app PRIVATE ${Boost_LIBRARIES} solver_library gui_library)

if (APPLE)
    target_link_libraries(app
        PRIVATE
        "-framework IOKit"
        "-framework Cocoa"
        "-framework OpenGL"
        "-framework CoreVideo")
endif()
