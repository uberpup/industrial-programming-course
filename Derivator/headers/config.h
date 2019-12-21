#ifndef DERIVATOR_CONFIG_H
#define DERIVATOR_CONFIG_H

#include <map>
#include <string>
#include "consts.h"

const std::string INITIAL_OUT_FILENAME = "../out_initial.dot";
const std::string OUT_FILENAME = "../out.dot";
const std::string OUT_SIMPLIFIED_FILENAME = "../out_simplified.dot";

const std::string FUNC_NAMES[] = {
        "$",
        "+",
        "-",
        "*",
        "/",
        "^",
        "sin",
        "cos",
        "x"
};

//std::map<std::string, int> FUNC_IDX = {{"sin", SIN},
//                                       {"cos", COS},
//                                       {"x", VARIABLE}};

#endif //DERIVATOR_CONFIG_H
