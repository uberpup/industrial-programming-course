#ifndef IMMORTALSTACK_DUMP_H
#define IMMORTALSTACK_DUMP_H

#include <cstdint>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <vector>

const char* DUMPFILENAME = "./dump_file";

template <typename T>
class Dump {

    Dump();
    Dump(const T& structure);

    void PrintFailMessage();
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
