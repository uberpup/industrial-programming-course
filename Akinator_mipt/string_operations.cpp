#include <algorithm>
#include <iostream>
#include <string>

std::string str_tolower(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c) { return std::tolower(c); }
    );
    return str;
}

char take_first_from_input() {
    std::string input;
    std::cin >> input;
    char in = input[0];     // Checking the first char of input,
    // ignoring the other part of it
    return in;
}


