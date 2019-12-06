#include "stack_machine.h"

void Preparation() {
    // todo заполнить словарь регистров и их номеров
}

void StackMachine::LoadBinary(const std::string &file) {
    // парсим бинарник
    // делаем вектор инструкций
    std::FILE* binary_file = std::fopen(file.c_str(), "r");
    std::fseek(binary_file, 0, SEEK_END);
    size_t file_size = std::ftell(binary_file);
    std::fseek(binary_file, 0, SEEK_SET);
    std::fread(instructions_.data(), 1, file_size, binary_file);
}

void StackMachine::Execute() {
    // todo выполняем вектор инструкций
}

int StackMachine::RegData(int idx) {
    return reg_[idx];
}

int StackMachine::RegData(const std::string_view& reg_name) {
    return reg_[reg_codes_[reg_name]];
}

float StackMachine::RegFData(int idx) {
    return reg_f_[idx];
}

float StackMachine::RegFData(const std::string_view& reg_name) {
    return reg_f_[reg_f_codes_[reg_name]];
}

