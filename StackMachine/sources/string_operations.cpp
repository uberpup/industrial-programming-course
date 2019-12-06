#include "string_operations.h"

std::string str_tolower(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c) { return std::tolower(c); }
    );
    return str;
}

char take_first_from_input() {
    std::string input;
    std::getline(std::cin, input);
    // Checking the first char of input,
    // ignoring the other part of it
    return input[0];
}

bool is_number(const std::string& str) {
    if (str.empty()) {
        return false;
    }
    return std::all_of(str.cbegin(), str.cend(),[](const char& c) {
        return isdigit(c);
    });
}