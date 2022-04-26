add_library(cgui_lib
        box_background.cpp
        cgui.cpp
        color.cpp
        color_utils.cpp
        geometry.cpp
        geometry_utils.cpp
        sized.cpp
        skia_canvas.cpp
        text.cpp
        )

target_link_libraries(cgui_lib PRIVATE SDL2 skia)
target_include_directories(cgui_lib
        PUBLIC ${CMAKE_SOURCE_DIR}/include
        )
