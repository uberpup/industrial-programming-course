#include "assembler.h"
#include "config.h"
#include "stack_machine.h"

int main() {
    // прочитать асм-код
    // перевести в байт-код
    Assembler ass;
    ass.Load(ASMCODE_FILENAME);
    ass.Assemble();
    // выполнить стековой машиной
    //StackMachine stack_machine;
    //stack_machine.LoadBinary(BINARYCODE_FILENAME);
    //stack_machine.Execute();

    return 0;
}