target_sources(cgui_lib PRIVATE
        colorutils.cpp
        )
target_include_directories(cgui_lib PRIVATE ${CMAKE_CURRENT_LIST_DIR})
# TODO: create colorutils.h somewhere
