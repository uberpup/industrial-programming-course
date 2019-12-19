#include "data.h"

void Data::ParseConfig(const std::string& filename) {
    std::FILE* file = std::fopen(filename.c_str(), "r");
    assert(file);

    TxtManager parser_txt_m;
    parser_txt_m.ReadFormat(file);

    this->op_names_.resize(parser_txt_m.strings.size());

    int32_t instruction_code_number = 1;
    size_t register_code_number = 0;
    size_t float_register_code_number = 0;
    bool parsing_instructions = false;      // file data starts with registers
    bool parsing_float_registers = false;

    for (auto& str : parser_txt_m.strings) {

        if (str == "/") {
            parsing_float_registers = true;
            continue;
        }

        if (str == "#") {
            parsing_instructions = true;
            continue;
        }

        if (!parsing_instructions) {
            if (parsing_float_registers) {
                this->reg_f_codes_.emplace(str, float_register_code_number);
                ++float_register_code_number;
            } else {
                this->reg_codes_.emplace(str, register_code_number);
                ++register_code_number;
            }
        }
    }
    std::fclose(file);

    //file = std::fopen(CONFIG_FILE.c_str(), "r");
    std::ifstream f(CONFIG_FILE);
    std::string str;
    size_t i = 0;
    while(getline(f, str)) {
        op_names_[i] = str;
        ++i;
    }
}