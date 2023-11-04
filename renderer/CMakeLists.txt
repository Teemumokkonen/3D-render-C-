cmake_minimum_required(VERSION 3.8)
project(3D_renderer)

include_directories(include)
find_package(SDL2)

add_library(datatypes src/datatypes.cpp include/datatypes.hpp)
add_library(renderer src/renderer.cpp include/renderer.hpp)

add_executable(window src/main.cpp)
target_link_libraries(window renderer SDL2 datatypes)

