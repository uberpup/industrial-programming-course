cmake_minimum_required(VERSION 3.14)
project(Akinator_mipt)

set(CMAKE_CXX_STANDARD 17)
include_directories(.)
include_directories(headers)
include_directories(sources)
add_executable(Akinator_mipt main.cpp headers/Akinator.h sources/Akinator.cpp headers/tree.h sources/tree.cpp sources/string_operations.cpp headers/tree_dot_converter.h sources/tree_dot_converter.cpp headers/string_operations.h)