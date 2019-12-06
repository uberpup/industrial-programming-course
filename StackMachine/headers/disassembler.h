#ifndef STACKMACHINE_DISASSEMBLER_H
#define STACKMACHINE_DISASSEMBLER_H

#include <string>

class Disassembler {
public:
    Disassembler();
    ~Disassembler();

    void Disassemble();
    void Load(const std::string& file);
    void Save(const std::string& file);

private:
    void Process();
    void Translate();
};

#endif //STACKMACHINE_DISASSEMBLER_H
