#include <cstdio>
#include <cassert>
#include "string_operations.h"
#include "assembler.h"

// todo метки, arg_code для меток
// todo кодогенерация - нужно содержание команд

void Assembler::Assemble() {
    Save(BINARYCODE_FILENAME);
}

void Assembler::Load(const std::string& filename) {
    std::FILE* file = std::fopen(filename.c_str(), "r");
    assert(file);
    txt_m_.ReadFormat(file); // Теперь в buf хранятся данные, в strings строки

    for (auto& str: txt_m_.strings) { // ищем метки
        size_t label_end = str.find(':');
        if (label_end == -1) {
            continue;
        }
        ParseLabel(str.substr(0, label_end));
        lexeme_parser_.AddPattern(str.substr(0, label_end), 0);
        labels_parser_.AddPattern(str.substr(0, label_end), 0);
    }

    Preparation();
    lexeme_parser_.Init();
    labels_parser_.Init();

    for (auto str : txt_m_.strings) {       // Instruction and label parsing

        if (lexeme_parser_.IsPresent(str)) {    // case of instruction with no arguments
            if (CheckArguments(str)) {
                Translate(str);
            }
            continue;
        }

        size_t instr_name_end = str.find(' ');
        if (instr_name_end == -1) {
            continue;
        }
        auto instr_name = str.substr(0, instr_name_end);
        if (!lexeme_parser_.IsPresent(instr_name)) {
            continue;
        }
        str = str.substr(instr_name_end + 1);
        size_t arg_f_end = str.find(' ');
        if (arg_f_end == -1) {
            if (CheckArguments(instr_name)) {
                Translate(instr_name);
            }
            continue;
        }
        auto arg_f = str.substr(0, arg_f_end);
        size_t arg_s_end = str.length();
        if (arg_s_end - arg_f_end < 1) {
            if (CheckArguments(instr_name, arg_f)) {
                Translate(instr_name, arg_f);
            }
            continue;
        }
        auto arg_s = str.substr(arg_f_end + 1);
        if (CheckArguments(instr_name, arg_f, arg_s)) {
            Translate(instr_name, arg_f, arg_s);
        }
    }
}

void Assembler::Save(const std::string& filename) {
    // выводим инструции в BINARYCODE_FILENAME
    // код команды код аргументов код команды ...
    std::FILE* binary_file = std::fopen(filename.c_str(), "w");
    assert(binary_file);

    for (auto& instruction : instructions_) {
        std::fwrite(&instruction.op_code, sizeof(instruction.op_code), 1, binary_file);
        fflush(binary_file);
        std::fwrite(&instruction.arg_code, sizeof(instruction.arg_code), 1, binary_file);
        fflush(binary_file);
        std::fwrite(&instruction.arg2_code, sizeof(instruction.arg2_code), 1, binary_file);
        fflush(binary_file);
    }

    std::fclose(binary_file);
}

void Assembler::Preparation() {

    std::FILE* file = std::fopen(IRCONFIG_FILENAME.c_str(), "r");
    assert(file);

    TxtManager parser_txt_m;
    parser_txt_m.ReadFormat(file);

    data_->op_names.resize(parser_txt_m.strings.size());

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
            lexeme_parser_.AddPattern(str, 0);

            if (parsing_float_registers) {
                data_->reg_f_codes_.emplace(str, float_register_code_number);
                ++float_register_code_number;
            } else {
                data_->reg_codes_.emplace(str, register_code_number);
                ++register_code_number;
            }
        } else {

            auto end = str.find(' ');
            lexeme_parser_.AddPattern(str.substr(0, end), 0);
            code_.insert({str.substr(0, end), instruction_code_number});

            ++instruction_code_number;
            if (str.substr(0, end) == str) {
                ParseInstructionArguments(str.substr(0, end), "");
            } else {
                ParseInstructionArguments(str.substr(0, end), str.substr(end + 1));
            }
        }
    }

    std::fclose(file);
}

void Assembler::Translate(const std::string& instruction,
        const std::string& arg_f, const std::string& arg_s) {
    // подразумеваем, что CheckArguments вызывается предварительно

    // 0000 - нет аргументов, 0100 - аргумент-метка, 1000 - аргумент-регистр,
    // 1010 - два регистра, 1011 - регистр-число, 1100 - аргумент-число, 1110 - число регистр, 1111 - число-число

    uint32_t code = 0;
    int32_t arg_code = 0;
    int32_t arg2_code = 0;
    int32_t sz = sizeof(code) * 8;

    if (!arg_f.empty() && !labels_parser_.IsPresent(arg_f)) {  // наличие первого аргумента не метки
        code += 1 << (sz - 1);
    }

    if (is_number(arg_f) || labels_parser_.IsPresent(arg_f)) {     // помечаем, что аргумент число, а не регистр
        code += 1 << (sz - 2);
        if (is_number(arg_f)) {
            arg_code += stoi(arg_f);
        }
    } else if (data_->reg_codes_.find(arg_f) != data_->reg_codes_.cend()) {        // если регистр, пишем его номер
        arg_code += data_->reg_codes_.at(arg_f);
    }

    if (!arg_s.empty()) {  // наличие второго аргумента
        code += 1 << (sz - 3);
    }

    if (is_number(arg_s)) {     // помечаем, что аргумент число, а не регистр
        code += 1 << (sz - 4);
        if (is_number(arg_s)) {
            arg2_code += stoi(arg_s);
        }
    } else if (data_->reg_codes_.find(arg_s) != data_->reg_codes_.cend()) {    // если регистр, пишем номер
        arg2_code += data_->reg_codes_.at(arg_s);
    }

    code += InstructionCode(instruction);

    auto current_instruction = Instruction {code, arg_code, arg2_code};
    instructions_.push_back(current_instruction);

    data_->op_names[InstructionCode(instruction)] = instruction;

    ++currently_parsed_instructions_;
}

bool Assembler::CheckArguments(const std::string& instruction,
        const std::string& arg_f, const std::string& arg_s) {
    std::string args;

    if (arg_f.empty()) {
        args = "";
    } else if (is_number(arg_f)) {
        args = "v";
    } else if (lexeme_parser_.IsPresent(arg_f)){
        if (arg_s.empty()) {
            args = "r";
        } else if (is_number(arg_s)) {
            args = "rv";
        } else if (lexeme_parser_.IsPresent(arg_s)) {
            args = "rr";
        }
    } else {
        return false;
    }

    if (labels_parser_.IsPresent(arg_f) && args.empty()) {
        args = "l";
    }

    return !(arguments_.find(std::make_pair(instruction, args)) == arguments_.end());
}

int32_t Assembler::InstructionCode(const std::string& instruction) {
    return code_.at(instruction);
}

void Assembler::ParseInstructionArguments(const std::string& instruction,
        const std::string& arguments) {
    std::string args = str_tolower(arguments);
    if (args == "rr" || args == "rv" || args == "r" || args == "v" ||
            args == "l" || args.empty()) {
        arguments_.insert(std::make_pair(instruction, args));
    } else {
        printf("%s\n", "Incorrect data");
    }
}

void Assembler::ParseLabel(const std::string& label_candidate) {
    if (!labels_parser_.IsPresent(label_candidate)) {
        return;
    }
    // todo ???
}