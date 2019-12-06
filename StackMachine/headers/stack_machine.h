#ifndef STACKMACHINE_STACK_MACHINE_H
#define STACKMACHINE_STACK_MACHINE_H

#include <cassert>
#include <iostream>
#include <map>
#include <stack>
#include <vector>
#include "config.h"
#include "instruction.h"

class StackMachine {
    // Registers: ax, bx, cx, dx, sp, fr, si, di
    // Instructions: pop, push, add, mul, imul, sub, div, mod, sqrt, in, out, end, jmp, je, jne, cmp
public:
    StackMachine() = default;
    ~StackMachine() = default;

    void Execute();

    void LoadBinary(const std::string& file);

    int RegData(int idx);
    int RegData(const std::string_view& reg_name);
    float RegFData(int idx);
    float RegFData(const std::string_view& reg_name);

private:
    void Preparation();

    std::stack<int> st_;
    std::map<std::string_view, size_t> reg_codes_;
    std::map<std::string_view, size_t> reg_f_codes_;
    float reg_f_[4];
    int reg_[8];
    std::vector<Instruction> instructions_;
};

#endif //STACKMACHINE_STACK_MACHINE_H
