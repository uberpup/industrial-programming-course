#include <algorithm>
#include <iostream>
#include <vector>
#include <random>
#include "int.h"

const size_t SIZE = 40;

int main() {
    std::cout << "Checking how integer works" << std::endl;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(-50, 50);
    std::vector<Int<int>> vec;
    vec.reserve(SIZE);
    for (int i = 0; i < SIZE; ++i) {
        vec.emplace_back(distribution(generator));
    }
    // std::sort check
    std::sort(vec.begin(), vec.end());
    std::cout << "Operations count " << _comparisons << std::endl;
    for (int i = 0; i < SIZE; ++i) {
        std::cout << vec[i] << std::endl;
    }
    return 0;
}
