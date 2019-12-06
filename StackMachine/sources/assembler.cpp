#include <cstdio>
#include <cassert>
#include "string_operations.h"
#include "assembler.h"

// todo Таски: метки, arg_code!
// todo Потом кодогенерация

void Assembler::Assemble() {
    Save(BINARYCODE_FILENAME);
}

void Assembler::Load(const std::string& filename) {
    std::FILE* file = std::fopen(filename.c_str(), "r");
    assert(file);
    Preparation();
    txt_m_.ReadFormat(file); // Теперь в buf хранятся данные, в strings строки

    for (auto& str: txt_m_.strings) { // ищем метки
        size_t label_end = str.find(':');
        if (label_end == -1) {
            continue;
        }
        lexeme_parser_.AddPattern(str.substr(0, label_end), 0);
        labels_parser_.AddPattern(str.substr(0, label_end), 0);
    }

    lexeme_parser_.Init();
    labels_parser_.Init();

    for (auto str : txt_m_.strings) {       // Instruction and label parsing

        size_t label_end = str.find(':');
        if (label_end != -1) {      // todo подумать над переключением состояния при переходе в метку
            ParseLabel(str.substr(0, label_end));
            continue;
        }

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
        // str = str.substr(arg_f_end + 1);
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
        // todo обработать случай метки
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
    }

    std::fclose(binary_file);
}

void Assembler::Preparation() {

    std::FILE* file = std::fopen(IRCONFIG_FILENAME.c_str(), "r");
    assert(file);

    TxtManager parser_txt_m;
    parser_txt_m.ReadFormat(file);
    int32_t code_number = 1;
    bool parsing_instructions = false;      // file data starts with registers
    for (auto& str : parser_txt_m.strings) {

        if (str == "#") {
            parsing_instructions = true;
            continue;
        }

        if (!parsing_instructions) {
            lexeme_parser_.AddPattern(str, 0);
        } else {
            auto end = str.find(' ');
            lexeme_parser_.AddPattern(str.substr(0, end), 0);
            code_.insert({str.substr(0, end), code_number});
            ++code_number;
            ParseInstructionArguments(str.substr(0, end), str.substr(end + 1));
        }
    }

    std::fclose(file);
}

void Assembler::Translate(const std::string& instruction,
        const std::string& arg_f, const std::string& arg_s) {
    // подразумеваем, что CheckArguments вызывается предварительно

    int32_t code = 0;
    int32_t sz = sizeof(code) * 8;

    if (!arg_f.empty()) {  // наличие первого аргумента
        code += 1 << (sz - 1);
    }

    if (is_number(arg_f)) {     // помечаем, что аргумент число, а не регистр
        code += 1 << (sz - 2);
    }

    if (!arg_s.empty()) {  // наличие второго аргумента
        code += 1 << (sz - 3);
    }

    if (is_number(arg_s)) {     // помечаем, что аргумент число, а не регистр
        code += 1 << (sz - 4);
    }

    code += InstructionCode(instruction);

    auto current_instruction = Instruction {code, 0}; // !! arg_code
    instructions_.push_back(current_instruction);
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