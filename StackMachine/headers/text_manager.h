#ifndef STACKMACHINE_TEXT_MANAGER_H
#define STACKMACHINE_TEXT_MANAGER_H

#include <cassert>
#include <cstdio>
#include <functional>
#include <string>
#include <string>
#include <vector>

const char SEPARATOR = '\n';
const char STRINGVIEW_SEPARATOR = '\0';


//! Struct uniting buffer, strings and operations among them
struct TxtManager {
    friend class Assembler;
    friend class StackMachine;
    friend class Disassembler;
    //! Trivial constructor
    TxtManager();

    //! Reading text from in_file and initialize both buf and strings
    void ReadFormat(std::FILE* in_file);

    //! fputs() of strings after sorting
    void WriteText(std::FILE* out_file);

    //! fputs() of strings in the default order
    void WriteBuf(std::FILE* out_file);

    //! Default destructor
    ~TxtManager() = default;
private:
    //! Allocating memory for buf using fseek() and ftell()
    void ReserveFileSize(std::FILE* in_file);

    //! Swapping amputated with attached in buf
    size_t Tokenize(char amputated, char attached);

    // Надо бы еще функцию удаления пустых строк

    std::vector<char> buf;
    std::vector<std::string> strings;
};

#endif //STACKMACHINE_TEXT_MANAGER_H
