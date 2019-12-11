#ifndef STACKMACHINE_INSTRUCTION_H
#define STACKMACHINE_INSTRUCTION_H

struct Instruction {
    uint32_t op_code;
    int32_t arg_code;
    int32_t arg2_code;
};

#endif //STACKMACHINE_INSTRUCTION_H
