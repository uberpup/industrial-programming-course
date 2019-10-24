#include "dump.h"
#include "im_stack.h"


template <class T>
class Dump<ImStack<T>> {
    const char* expression;
    const char* file_name;
    std::string message;
    std::vector<const char *> dump_message;
    size_t line_number;

    const char* type_name;
    const void* address;
    const size_t structure_size;
    const T* data;

    Dump(): structure_size(0), data(), type_name(), line_number(0),
                     expression(), file_name(), message(), dump_message() {}

    Dump(const char* const expr, const char* const file_name,
                  size_t line_number, const char* const msg, const T& structure)
                  : expression(expr),
                    file_name(file_name), line_number(line_number),
                    message(msg), dump_message() {

        address = &structure;
        type_name = typeid(T).name();
        structure_size = structure.sz;
        data = std::move(structure.data);
    }

    void GenerateFailMessage() {
        dump_message.push_back("Failed! from" + file_name);
        dump_message.push_back(type_name + "on" + address);
        dump_message.push_back("Error code = ");
        dump_message.push_back("size = " + structure_size);
        for (size_t i = 0; i < structure_size; ++i) {
            dump_message.push_back("data[" + std::to_string(i) + "] = " + data[i]);
        }
    }

    void PrintFailMessage() {
        for (const auto& str : dump_message) {
            printf("%s\n", str);
        }
    }

};

/*
 * Failed! from file_name
 *      Structure_name<T> with T = type_name [ptr] member_name {
 *      Errcode =
 *      sz =
 *      data[capacity--][ptr] = {
 *          *[0] =
 *          ...
 *          [3] = -666(POISON)
 *          [4] = -666(POISON)
 *      }
 * }
 */