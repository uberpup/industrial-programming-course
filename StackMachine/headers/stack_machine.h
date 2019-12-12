#ifndef STACKMACHINE_STACK_MACHINE_H
#define STACKMACHINE_STACK_MACHINE_H

#include <cassert>
#include <cinttypes>
#include <cmath>
#include <iostream>
#include <map>
#include <stack>
#include <vector>
#include "common_data.h"
#include "config.h"
#include "instruction.h"
#include "text_manager.h"

class StackMachine {
    // Registers: ax, bx, cx, dx, sp, fr, si, di
    // Instructions: pop, push, add, mul, imul, sub, div, mod, sqrt, in, out, end, jmp, je, jne, cmp
public:
    StackMachine() = default;
    ~StackMachine() = default;
    explicit StackMachine(Data* data) : data_(data) {}

    void Execute();

    void LoadBinary(const std::string& file);

    int RegData(int idx);
    int RegData(const std::string& reg_name);
    float RegFData(int idx);
    float RegFData(const std::string& reg_name);

private:
    inline void ParseInstruction(const Instruction& op, std::FILE* input,
            std::FILE* output, bool& in_label, size_t& idx);
    Data* data_;
    std::stack<int> st_;
    float reg_f_[4];
    int reg_[8];
    bool eq_flag = false;
    bool less_flag = false;
    std::vector<Instruction> instructions_;
};

#endif //STACKMACHINE_STACK_MACHINE_H
