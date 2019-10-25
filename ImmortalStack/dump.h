#ifndef IMMORTALSTACK_DUMP_H
#define IMMORTALSTACK_DUMP_H

#include <cstdint>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <vector>

const char* DUMPFILENAME = "./dump_file";

//! Template Dump class
template <typename T>
class Dump {

    Dump();
    Dump(const T& structure);

    //! Prints dump_message in dump_file
    void PrintFailMessage();
    //! Generates dump_message in dump_file
    void GenerateFailMessage();

    std::FILE* dump_file = std::fopen(DUMPFILENAME, "w");
    const char* dump_message;
    const char* type_name;
    const void* address;
    const size_t structure_capacity;
    const T* data;


    ~Dump() = default;
};

#endif //IMMORTALSTACK_DUMP_H
