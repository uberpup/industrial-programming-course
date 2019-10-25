#include "dump.h"
#include "im_stack.h"


template <class T>
class Dump<ImStack<T>> {

    Dump(): structure_capacity(0), data(), type_name(), dump_message(),
            address() {}

    explicit Dump(const T& structure)
                  : dump_message() {

        address = &structure;
        type_name = typeid(T).name();
        structure_capacity = structure.capacity;
        data = std::move(structure.data);

        GenerateFailMessage();
        PrintFailMessage();
    }

    void GenerateFailMessage() {
        dump_message = "Failure on" + address;
    }

    void PrintFailMessage() {
        fprintf(dump_file, "%s\n", dump_message);
        fprintf(dump_file, "%s\n", "data: ");
        for (size_t i = 0; i < structure_capacity; ++i) {
            fprintf(dump_file, "%s\n", data[i]);
        }
    }


    std::FILE* dump_file = std::fopen(DUMPFILENAME, "w");
    const char* dump_message;
    const char* type_name;
    const void* address;
    const size_t structure_capacity;
    const T* data;

    ~Dump() {
        std::fclose(dump_file);
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

/*dump_message.push_back("Failed! from" + file_name);
    dump_message.push_back(type_name + "on" + address);
    dump_message.push_back("Error code = ");
    dump_message.push_back("size = " + structure_capacity);
    for (size_t i = 0; i < structure_capacity; ++i) {
        dump_message.push_back("data[" + std::to_string(i) + "] = " + data[i]);
*/
