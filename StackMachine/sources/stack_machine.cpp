#include "stack_machine.h"

void StackMachine::LoadBinary(const std::string& file) {
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
    for (const auto& op : instructions_) {
        auto op_code = op.op_code;
        #include "operations.cpp"
    }
}

int StackMachine::RegData(int idx) {
    return reg_[idx];
}

int StackMachine::RegData(const std::string& reg_name) {
    return reg_[data->reg_codes_[reg_name]];
}

float StackMachine::RegFData(int idx) {
    return reg_f_[idx];
}

float StackMachine::RegFData(const std::string& reg_name) {
    return reg_f_[data->reg_f_codes_[reg_name]];
}
