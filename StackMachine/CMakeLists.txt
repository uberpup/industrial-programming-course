cmake_minimum_required(VERSION 3.14)
project(StackMachine)

set(CMAKE_CXX_STANDARD 17)
include_directories(.)
execute_process(COMMAND python3 ../codegeneration.py)
include_directories(headers)
include_directories(sources)
add_executable(StackMachine main.cpp sources/stack_machine.cpp headers/config.h headers/stack_machine.h
        sources/assembler.cpp headers/assembler.h headers/disassembler.h sources/disassembler.cpp headers/text_manager.h sources/text_manager.cpp headers/instruction.h headers/bohr.h sources/bohr.cpp headers/string_operations.h sources/string_operations.cpp sources/operations.cpp headers/common_data.h)