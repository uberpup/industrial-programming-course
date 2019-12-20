cmake_minimum_required(VERSION 3.15)
project(Derivator)

set(CMAKE_CXX_STANDARD 17)
include_directories(.)
include_directories(headers)
include_directories(sources)
add_executable(Derivator main.cpp headers/tree_dot_converter.h sources/tree_dot_converter.cpp headers/derivator.h
        sources/derivator.cpp headers/tree.h sources/tree.cpp headers/consts.h headers/config.h)