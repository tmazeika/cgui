cmake_minimum_required(VERSION 3.21)
project(cgui
        VERSION 0.1.0
        LANGUAGES CXX
        )
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(extern)
add_subdirectory(src)

# TODO: move to examples/
add_executable(cgui_example1 examples/example1.cpp)
target_link_libraries(cgui_example1 PRIVATE cgui_lib)
