#include "assembler.h"
#include "data.h"
#include "config.h"
#include "data.h"
#include "stack_machine.h"

int main() {
    Data data;
    data.ParseConfig(IRCONFIG_FILENAME);
    StackMachine stack_machine(&data);
    stack_machine.LoadBinary(BINARYCODE_FILENAME);
    stack_machine.Execute();
}