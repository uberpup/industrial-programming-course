cmake_minimum_required(VERSION 3.14)
project(Akinator_mipt)

set(CMAKE_CXX_STANDARD 17)

add_executable(Akinator_mipt main.cpp Akinator.h Akinator.cpp tree.h tree.cpp string_operations.cpp)