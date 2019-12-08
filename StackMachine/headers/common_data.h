#ifndef STACKMACHINE_COMMON_DATA_H
#define STACKMACHINE_COMMON_DATA_H

#include <map>

class Data {
    friend class Assembler;
    friend class StackMachine;
    friend class Disassembler;

private:
    std::map<std::string, size_t> reg_codes_;
    std::map<std::string, size_t> reg_f_codes_;
};

#endif //STACKMACHINE_COMMON_DATA_H
