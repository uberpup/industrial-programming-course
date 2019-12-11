#ifndef STACKMACHINE_OPERATIONS_DESCRIPTION_H
#define STACKMACHINE_OPERATIONS_DESCRIPTION_H

#include "execution_define.h"

EXECUTE_OPERATION(op_name == "push r",  st_.push(RegData(r)););

EXECUTE_OPERATION(op_name == "push v", st_.push(v););

EXECUTE_OPERATION(op_name == "pop r", st_.pop(); );

EXECUTE_OPERATION(op_name == "pop v", st_.pop(); );

EXECUTE_OPERATION(op_name == "mul r", reg_[data_->reg_codes_.at("ax")] *= reg_[r]; );

EXECUTE_OPERATION(op_name == "mul v", reg_[data_->reg_codes_.at("ax")] *= v; );

EXECUTE_OPERATION(op_name == "imul rr", reg_[r] *= reg_[r1]; );

EXECUTE_OPERATION(op_name == "imul rv", reg_[r] *= v; );

EXECUTE_OPERATION(op_name == "add rr", reg_[r] += reg_[r1]; )

EXECUTE_OPERATION(op_name == "add rv", reg_[r] += v; )

EXECUTE_OPERATION(op_name == "sub rr", reg_[r] -= reg_[r1]; );

EXECUTE_OPERATION(op_name == "sub rv", reg_[r] -= v; );

EXECUTE_OPERATION(op_name == "div rr", reg_[r] /= reg_[r1]; );

EXECUTE_OPERATION(op_name == "div rv", reg_[r] /= v; );

EXECUTE_OPERATION(op_name == "mov rr", reg_[r] = reg_[r1]; );

EXECUTE_OPERATION(op_name == "mov rv", reg_[r] = v; );

EXECUTE_OPERATION(op_name == "sqrt r",  reg_[r] = sqrt(reg_[r]); );

EXECUTE_OPERATION(op_name == "sqrt rv",  reg_[r] = sqrt(v); );

EXECUTE_OPERATION(op_name == "in", fscanf(input, "%ld", &in_v); st_.push(in_v); );

EXECUTE_OPERATION(op_name == "in v", st_.push(v); )

EXECUTE_OPERATION(op_name == "out", fprintf(output, "%ld\n", st_.top()); );

EXECUTE_OPERATION(op_name == "out r", fprintf(output, "%ld\n", reg_[r]); );

EXECUTE_OPERATION(op_name == "end", std::fclose(output); exit(0); );

EXECUTE_OPERATION(op_name == "cmp rr", if (reg_[r] == reg_[r1]) eq_flag = true; if (reg_[r] < reg_[r1]) less_flag = true; );

EXECUTE_OPERATION(op_name == "cmp rv", if (reg_[r] == v) eq_flag = true; if (reg_[r] < v) less_flag = true;);

EXECUTE_OPERATION(op_name == "jne l", if (!eq_flag) { in_label = true; idx = arg_code - 1; } );

EXECUTE_OPERATION(op_name == "je l", if (eq_flag) { in_label = true; idx = arg_code - 1; } );

EXECUTE_OPERATION( op_name == "jl l", if (less_flag) { in_label = true; idx = arg_code - 1; } );

EXECUTE_OPERATION(op_name == "jle l", if (less_flag || eq_flag) { in_label = true; idx = arg_code - 1; } );

EXECUTE_OPERATION(op_name == "jg l", if (!less_flag && !eq_flag) { in_label = true; idx = arg_code - 1; } );

EXECUTE_OPERATION(op_name == "jge l", if (!less_flag) { in_label = true; idx = arg_code - 1; } );

EXECUTE_OPERATION(op_name == "jmp l", in_label = true; idx = arg_code - 1; );


#endif //STACKMACHINE_OPERATIONS_DESCRIPTION_H
