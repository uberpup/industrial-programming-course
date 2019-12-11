#ifndef STACKMACHINE_CONFIG_H
#define STACKMACHINE_CONFIG_H

#include <cstdio>

constexpr size_t STACK_SIZE = 1024;
const std::string ASMCODE_FILENAME = "../tests/quadratic.s";
const std::string BINARYCODE_FILENAME = "../binary.txt";
const std::string IRCONFIG_FILENAME = "../instruction_register_set.txt";
const std::string OUTPUT_FILE = "../output.txt";
const std::string INPUT_FILE = "../input.txt";

#endif //STACKMACHINE_CONFIG_H
