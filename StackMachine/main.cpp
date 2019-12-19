#include "assembler.h"
#include "data.h"
#include "config.h"
#include "stack_machine.h"

int main() {
    Data data;
    Assembler ass(&data);
    ass.Load(ASMCODE_FILENAME);
    ass.Assemble();
    StackMachine stack_machine(&data);
    stack_machine.LoadBinary(BINARYCODE_FILENAME);
    stack_machine.Execute();
    return 0;
}