target_sources(cgui_lib PRIVATE
        canvas.cpp
        color.cpp
        )
# TODO: don't think this should be here:
target_include_directories(cgui_lib PRIVATE ${CMAKE_CURRENT_LIST_DIR})
