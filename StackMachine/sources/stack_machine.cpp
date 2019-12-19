#include "stack_machine.h"

void StackMachine::LoadBinary(const std::string& file) {
    std::FILE* binary_file = std::fopen(file.c_str(), "r");
    std::fseek(binary_file, 0, SEEK_END);
    size_t file_size = std::ftell(binary_file);
    std::fseek(binary_file, 0, SEEK_SET);
    instructions_.resize(file_size / (sizeof(Instruction)));
    std::fread(instructions_.data(), 1, file_size, binary_file);
}

void StackMachine::Execute() {
    std::FILE* output = std::fopen(OUTPUT_FILE.c_str(), "w");
    std::FILE* input = std::fopen(INPUT_FILE.c_str(), "r");

    size_t i = 0;
    ssize_t return_idx = -1;
    bool in_label = false;
    while (i < instructions_.size()) {
        if (instructions_[i].op_code != 0 && !in_label)    return_idx = i;
        if (in_label && instructions_[i].op_code == 0) {    // пустая инструкция - выход из метки
            i = return_idx + 1;
            in_label = false;
        }
        while (instructions_[i].op_code == 0)   ++i;
        ParseInstruction(instructions_[i], input, output, in_label, i);
        ++i;
    }

}

inline void StackMachine::ParseInstruction(const Instruction& op,
        std::FILE* input, std::FILE* output, bool& in_label,
        size_t& idx) {

    auto op_code = op.op_code;
    auto arg_parsing_code = (op_code >> (sizeof(op_code) * 8 - 4));
    auto shift = (arg_parsing_code << (sizeof(op_code) * 8 - 4));
    auto op_parsing_code = op_code - shift;
    auto arg_code = op.arg_code;
    auto arg2_code = op.arg2_code;

    int32_t r = 0;
    int32_t r1 = 0;
    int32_t v = 0;
    int32_t v1 = 0;
    int32_t in_v = 0;
    std::string op_name;

    // translating code to name
    op_name = data_->op_names_[op_parsing_code];
    // parsing arguments
    switch (arg_parsing_code) {
        case 0b0:
            break;
        case 0b100:
            // label
            op_name += " l";
            break;
        case 0b1000:
            r = arg_code;
            op_name += " r";
            break;
        case 0b1010:
            r = arg_code;
            r1 = arg2_code;
            op_name += " rr";
            break;
        case 0b1011:
            r = arg_code;
            v = arg2_code;
            op_name += " rv";
            break;
        case 0b1100:
            v = arg_code;
            op_name += " v";
            break;
        case 0b1110:
            r = arg_code;
            v = arg2_code;
            op_name += " rv";
            break;
        case 0b1111:
            v = arg_code;
            v1 = arg2_code;
            op_name += " vv";
            break;
        default:
            assert(false);
    }
    #include "operations_description.h"
}

int StackMachine::RegData(int idx) {
    return reg_[idx];
}

int StackMachine::RegData(const std::string& reg_name) {
    return reg_[data_->reg_codes_[reg_name]];
}

float StackMachine::RegFData(int idx) {
    return reg_f_[idx];
}

float StackMachine::RegFData(const std::string& reg_name) {
    return reg_f_[data_->reg_f_codes_[reg_name]];
}
