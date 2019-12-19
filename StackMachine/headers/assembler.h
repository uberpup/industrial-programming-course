#ifndef STACKMACHINE_ASSEMBLER_H
#define STACKMACHINE_ASSEMBLER_H

#include <cstring>
#include <map>
#include <set>
#include "data.h"
#include "config.h"
#include "bohr.h"
#include "instruction.h"
#include "text_manager.h"

class Assembler {
public:
    Assembler() = default;
    ~Assembler() = default;
    explicit Assembler(Data* data) : data_(data){};

    void Assemble();
    void Load(const std::string& filename);
    void Save(const std::string& filename);

private:
    void Preparation();

    void Translate(const std::string& instruction,
            const std::string& arg_f = "",
            const std::string& arg_s = "");

    bool CheckArguments(const std::string& instruction,
            const std::string& arg_f = "",
            const std::string& arg_s = "");

    int32_t InstructionCode(const std::string& instruction);

    void ParseInstructionArguments(const std::string& instruction,
            const std::string& arguments);
    void ParseLabel(const std::string& label_candidate);
    void FillWaitlist();

    Data* data_ = nullptr;
    TxtManager txt_m_;
    Bohr lexeme_parser_;
    Bohr labels_parser_;
    std::map<std::string, int32_t> code_;
    std::set<std::pair<std::string, std::string>> arguments_;
    std::vector<Instruction> instructions_;
    std::vector<std::pair<std::string, size_t>> waitlist_;
    size_t currently_parsed_instructions_ = 0;
};

#endif //STACKMACHINE_ASSEMBLER_H
