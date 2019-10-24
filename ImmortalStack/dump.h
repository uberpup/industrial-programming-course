#ifndef IMMORTALSTACK_DUMP_H
#define IMMORTALSTACK_DUMP_H

#include <cstdint>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <vector>

template <typename T>
class Dump {
    Dump();
    Dump(const char* const expr, const char* const file_name,
         size_t line_number, const char* const msg, const T& structure);
    void PrintFailMessage();
    void GenerateFailMessage();

    const char* expression;
    const char* file_name;
    std::string message;
    std::vector<std::string> dump_message;
    size_t line_number;

    const char* type_name;
    const void* address;
    const size_t structure_size;
    const T* data;


    ~Dump() = default;
};

#endif //IMMORTALSTACK_DUMP_H
