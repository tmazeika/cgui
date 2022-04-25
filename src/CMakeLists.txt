add_library(cgui_lib
        cgui.cpp
        )

add_subdirectory(box)
add_subdirectory(geometry)
add_subdirectory(graphics)
add_subdirectory(internal)

target_link_libraries(cgui_lib PRIVATE SDL2 skia)
target_include_directories(cgui_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)
