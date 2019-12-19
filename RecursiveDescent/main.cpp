#include <cassert>
#include <iostream>

// G - grammar
// N - correct numbers
// E - correct expressions
// T - correct terms
// P - correct bracket sequence

int RecursiveDescent(const std::string_view& str);

int GetN(const std::string_view& str, size_t& idx);

int GetE(const std::string_view& str, size_t& idx);

int GetT(const std::string_view& str, size_t& idx);

int GetP(const std::string_view& str, size_t& idx);


int main() {
    std::string input;
    printf("%s\n", "Input the parsed string");
    std::cin >> input;
    printf("%d\n", RecursiveDescent(input));
    return 0;
}

int RecursiveDescent(const std::string_view& str) {
    size_t idx = 0;
    auto value = GetE(str, idx);
    assert(str[idx] == '#');
    return value;
}

inline int GetE(const std::string_view& str, size_t& idx) {
    auto value = GetT(str, idx);
    while (str[idx] == '-' || str[idx] == '+') {
        char operation = str[idx];
        ++idx;
        auto next_value = GetT(str, idx);
        if (operation == '+') {
            value += next_value;
        }
        if (operation == '-') {
            value -= next_value;
        }
    }
    return value;
}

inline int GetT(const std::string_view& str, size_t& idx) {
    auto value = GetP(str, idx);
    while (str[idx] == '*' || str[idx] == '/') {
        char operation = str[idx];
        ++idx;
        auto next_value = GetP(str, idx);
        if (operation == '*') {
            value *= next_value;
        }
        if (operation == '/') {
            value /= next_value;
        }
    }
    return value;
}

inline int GetP(const std::string_view& str, size_t& idx) {
    if (str[idx] == '(') {
        ++idx;
        auto value = GetE(str, idx);
        assert(str[idx] == ')');
        ++idx;
        return value;
    } else {
        return GetN(str, idx);
    }
}

inline int GetN(const std::string_view& str, size_t& idx) {
    int value = 0;
    if (str[idx] >= '0' && str[idx] <= '9') {
        value *= 10;
        value += str[idx] - '0';
        ++idx;
    }
    return value;
}