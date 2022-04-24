add_library(cgui_lib
        cgui.cpp
        geometry.cpp
        )
target_link_libraries(cgui_lib PRIVATE SDL2 skia)
target_include_directories(cgui_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)
