cmake_minimum_required(VERSION 3.21)
project(cgui
        VERSION 0.1.0
        LANGUAGES C CXX
        )
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(extern)
add_subdirectory(src)
add_subdirectory(examples)
