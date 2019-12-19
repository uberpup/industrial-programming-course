#ifndef STACKMACHINE_DATA_H
#define STACKMACHINE_DATA_H

#include "config.h"
#include "text_manager.h"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class Data {
    friend class Assembler;
    friend class StackMachine;
    friend class Disassembler;
public:
    void ParseConfig(const std::string& filename);
private:
    std::map<std::string, size_t> reg_codes_;
    std::map<std::string, size_t> reg_f_codes_;
    std::map<std::string, size_t> label_idx_;
    std::vector<std::string> op_names_;
};

#endif //STACKMACHINE_DATA_H
