#include <iostream>
#include "config.h"
#include "derivator.h"

int main() {
    std::string expression;
    Derivator derivator;
    std::cin >> expression;
    if (expression.back() != '#') {
        expression += '#';
    }
    derivator.Build(expression);
    derivator.SaveTree(INITIAL_OUT_FILENAME);
    derivator.TakeDerivative(derivator.root_);
    derivator.SaveTree(OUT_FILENAME);
    //if (derivator.Simplify(derivator.root_)) {
    //    std::cout << "success in simplification" << std::endl;
    //    derivator.SaveTree(OUT_SIMPLIFIED_FILENAME);
    //}
    return 0;
}
