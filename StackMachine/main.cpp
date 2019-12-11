#include "assembler.h"
#include "common_data.h"
#include "config.h"
#include "stack_machine.h"

int main() {
    // прочитать асм-код
    // перевести в байт-код
    Data data;
    Assembler ass(&data);
    ass.Load(ASMCODE_FILENAME);
    ass.Assemble();
    // выполнить стековой машиной
    StackMachine stack_machine(&data);
    stack_machine.LoadBinary(BINARYCODE_FILENAME);
    stack_machine.Execute();

    return 0;
}